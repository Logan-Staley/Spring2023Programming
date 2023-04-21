

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;



public class HeartFailure_Prediction {


    public static void main(String[] args) {

        String filePath4features = "Termproject/heart_failure_clinical_records_dataset_cleaned.csv";
        //imports the CVS file to be read

        String csvSplitBy = ",";
        String line = "";
        System.out.println("Reading CSV file: " + filePath4features);
        List<List<Double>> X = new ArrayList<>();
        List<Integer> y = new ArrayList<>();
        //declares the variables for splitting the data along with providing context for what is being ran

        //starts a try in for reading the values from the CVS file and seperates the comma seperated values and place them into Double List
        //and provides a nice format for them to be accessed later
    
                try (BufferedReader br = new BufferedReader(new FileReader(filePath4features))) {
                    String headerLine = br.readLine();
                    System.out.println("Header: " + headerLine);
                    int rowCount = 0;
                    while ((line = br.readLine()) != null) {
                        rowCount++;
                        String[] filePath4features_data = line.split(csvSplitBy);
                        System.out.println("Row " + rowCount + ": " + Arrays.toString(filePath4features_data));
                        // Process the data here
                        int labelIndex = filePath4features_data.length - 1;
                        y.add(Integer.parseInt(filePath4features_data[labelIndex]));
                        System.out.println("y: " + y);
                        //System.out.println(y.toString(labelIndex));
                        List<Double> features = new ArrayList<>();
                        features.add(1.0); // Add x0 = 1 for the bias term
            
                        for (int i = 0; i < labelIndex; i++) {
                            
                            features.add(Double.parseDouble(filePath4features_data[i]));
                        }
            
                        X.add(features);
                        System.out.println("X: " + X);
                    }
                
                } catch (IOException e) {
                    e.printStackTrace();
                }
                
                System.out.println("The Code ran");
        
              if (X.isEmpty()) {
                System.out.println("No data found in the CSV file.");
                return;
            }
            //catch for error checking along with validation that code was ran to this point






    }
}
