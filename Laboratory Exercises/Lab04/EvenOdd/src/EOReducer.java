import java.io.IOException; 
import java.util.Iterator; 
import org.apache.hadoop.io.IntWritable; 
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.mapred.MapReduceBase; 
import org.apache.hadoop.mapred.OutputCollector; 
import org.apache.hadoop.mapred.Reducer; 
import org.apache.hadoop.mapred.Reporter; 
  
public class EOReducer extends MapReduceBase implements Reducer<Text, 
                                   IntWritable, Text, IntWritable> { 
  
    @Override
    // Reduce Function 
    public void reduce(Text key, Iterator<IntWritable> value, 
     OutputCollector<Text, IntWritable> output, Reporter rep) 
  
    throws IOException 
    { 
  
        // For finding sum and count of even and odd 
        // you don't have to take different variables 
        int sum = 0, count = 0; 
        if (key.equals("ODD"))  
        { 
            while (value.hasNext()) 
            { 
                IntWritable i = value.next(); 
  
                // Finding sum and count of ODD Numbers 
                sum += i.get(); 
                count++; 
            } 
        } 
  
        else 
        { 
            while (value.hasNext())  
            { 
                IntWritable i = value.next(); 
  
                // Finding sum and count of EVEN Numbers 
                sum += i.get(); 
                count++; 
            } 
        } 
  
        // First sum then count is printed 
        output.collect(key, new IntWritable(sum)); 
        output.collect(key, new IntWritable(count)); 
    } 
} 