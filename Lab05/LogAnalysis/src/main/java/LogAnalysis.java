import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.*;

import java.io.IOException;
import java.util.*;

public class LogAnalysis {
    public static class Map extends MapReduceBase implements Mapper<LongWritable, Text, Text, Text> {
        public void map(LongWritable key, Text value, OutputCollector<Text, Text> output, Reporter reporter) throws IOException {
            List<String> lines = Arrays.asList(value.toString().split("\n"));
            lines.forEach(line -> {
                String month = line.split("/")[1];
                String ip = line.split("\\s")[0];
                try {
                    output.collect(new Text(month), new Text(ip));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }
    }

    public static class Reduce extends MapReduceBase implements Reducer<Text, Text, Text, Set<Text>> {
        public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, Set<Text>> output, Reporter reporter) throws IOException {
            Set<Text> addresses = new HashSet<>();

            while(values.hasNext()){
                addresses.add(values.next());
            }

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
