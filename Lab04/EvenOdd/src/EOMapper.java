import java.io.IOException; 
import org.apache.hadoop.io.IntWritable; 
import org.apache.hadoop.io.LongWritable; 
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.mapred.MapReduceBase; 
import org.apache.hadoop.mapred.Mapper; 
import org.apache.hadoop.mapred.OutputCollector; 
import org.apache.hadoop.mapred.Reporter; 
  
public class EOMapper extends MapReduceBase implements Mapper<LongWritable, 
                                                 Text, Text, IntWritable> { 
  
    @Override
    // Map function 
    public void map(LongWritable key, Text value, OutputCollector<Text,  
                                     IntWritable> output, Reporter rep) 
  
    throws IOException 
    { 
        // Splitting the line into spaces 
        String data[] = value.toString().split(" "); 
  
        for (String num : data)  
        { 
  
            int number = Integer.parseInt(num); 
  
            if (number % 2 == 1)  
            { 
                // For Odd Numbers 
                output.collect(new Text("ODD"), new IntWritable(number)); 
            } 
  
            else 
            { 
                // For Even Numbers 
                output.collect(new Text("EVEN"),  
                       new IntWritable(number)); 
            } 
        } 
    } 
} 
