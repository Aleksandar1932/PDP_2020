import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.*;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.*;

public class LogAnalysis {
    public static class Map extends MapReduceBase implements Mapper<LongWritable, Text, Text, Text> {
        private String getMonthAndFileKeyFromLogLine(String line) {
            String month = line.split("/")[1];
            String file = Paths.get(line.split("GET")[1].split("HTTP")[0]).getFileName().toString();

            return String.format("%s %s", month, file);
        }

        private String getIpFromLogLine(String line) {
            return line.split("\\s")[0];
        }

        public void map(LongWritable key, Text value, OutputCollector<Text, Text> output, Reporter reporter) {
            List<String> lines = Arrays.asList(value.toString().split("\n"));
            lines.forEach(line -> {
                String monthAndFileKey = getMonthAndFileKeyFromLogLine(line);
                String ip = getIpFromLogLine(line);
                try {
                    output.collect(new Text(monthAndFileKey), new Text(ip));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }
    }

    public static class Reduce extends MapReduceBase implements Reducer<Text, Text, Text, Set<String>> {
        public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, Set<String>> output, Reporter reporter) throws IOException {
            Set<String> addresses = new HashSet<>();
            values.forEachRemaining(value -> addresses.add(value.toString()));
            output.collect(key, addresses);
        }
    }

    public static void main(String[] args) throws Exception {
        JobConf conf = new JobConf(LogAnalysis.class);
        conf.setJobName("LogAnalysis");

        conf.setMapOutputValueClass(Text.class);
        conf.setOutputKeyClass(Text.class);
        conf.setOutputValueClass(Set.class);

        conf.setMapperClass(LogAnalysis.Map.class);
        conf.setReducerClass(LogAnalysis.Reduce.class);

        conf.setInputFormat(TextInputFormat.class);
        conf.setOutputFormat(TextOutputFormat.class);

        FileInputFormat.setInputPaths(conf, new Path(args[0]));
        FileOutputFormat.setOutputPath(conf, new Path(args[1]));

        JobClient.runJob(conf);
    }
}
