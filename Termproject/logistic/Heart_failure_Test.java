package Termproject.logistic;

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;







public class Heart_failure_Test {


 public static void main(String[] args) {
        String filePath4features = "Termproject/heart_failure_clinical_records_dataset_cleaned.csv";
        ///String filePath_age_serum_sodium = "heart_failure_clinical_records_dataset_cleaned_serum_sodium.csv";
        //String filePath_age_serum_creatinine = "heart_failure_clinical_records_dataset_cleaned_serum_creatinine.csv";
        //String filePath_age_ejection_fraction = "heart_failure_clinical_records_dataset_cleaned_ejection_fraction.csv";
        String csvSplitBy = ",";
        String line = "";
        System.out.println("Reading CSV file: " + filePath4features);
        List<List<Double>> X = new ArrayList<>();
        List<Double> y = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath4features))) {
            String headerLine = br.readLine();
            System.out.println("Header: " + headerLine);
            int rowCount = 0;
            while ((line = br.readLine()) != null) {
                String[] fields = line.split(csvSplitBy);

                // Convert the fields to doubles and add them to the X list
                List<Double> row = new ArrayList<>();
                 // Add a bias term of 1.0
                 row.add(1.0); // Add a bias term of 1.0
                 row.add(Double.parseDouble(fields[0])); // Add ejection fraction
                 row.add(Double.parseDouble(fields[1])); // Add serum creatinine
                 row.add(Double.parseDouble(fields[2])); // Add serum sodium
                 X.add(row);
                
                // Add the label (if it exists) to the y list
                if (fields.length > 3) {
                    y.add(Double.parseDouble(fields[3]));

                }
            }
        
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("X: " + X);
        System.out.println("y: " + y);
        System.out.println("The Code ran");

      if (X.isEmpty()) {
        System.out.println("No data found in the CSV file.");
        return;
    }   
    }
}
/// OK so i got the CSV file to be inputed in to Linked list X with Bias inputed long with the correct values to each one

//now just get the logistic regression to start and provide accurate eastimations on another heart failure to happen

//look into the python graphing like in the previous assignments to get graphs of the perceptron and linear regression predictions of people having heart failure again

// look at micheals github for examples. https://github.com/michaelank2049/Year-3-Semester-2/tree/main/LankfordMTermProject