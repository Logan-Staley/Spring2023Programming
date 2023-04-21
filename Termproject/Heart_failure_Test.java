package Termproject;

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;







public class Heart_failure_Test {



    public static double sigmoid(double x) {
        return 1 / (1 + Math.exp(-x));
    }

    public static double dotProduct(List<Double> vector1, List<Double> vector2) {
        if (vector1.size() != vector2.size()) {
            throw new IllegalArgumentException("Vectors must have the same size");
        }
    
        double result = 0;
        for (int i = 0; i < vector1.size(); i++) {
            result += vector1.get(i) * vector2.get(i);
        }
    
        return result;
    }

    public static double logisticRegressionCost(List<List<Double>> X, List<Integer> y, List<Double> theta) {
        int m = y.size();
        double cost = 0;

        for (int i = 0; i < m; i++) {
            double h = sigmoid(dotProduct(X.get(i), theta));
            cost += -y.get(i) * Math.log(h) - (1 - y.get(i)) * Math.log(1 - h);
        }

        return cost / m;
    }

    public static List<Double> gradientDescent(List<List<Double>> X, List<Integer> y, List<Double> theta, double alpha, int numIterations) {
        int m = y.size();
        int n = theta.size();
        List<Double> newTheta = new ArrayList<>(theta);

        for (int iter = 0; iter < numIterations; iter++) {
            List<Double> gradient = new ArrayList<>(n);

            for (int j = 0; j < n; j++) {
                double sum = 0;

                for (int i = 0; i < m; i++) {
                    double h = sigmoid(dotProduct(X.get(i), newTheta));
                    sum += (h - y.get(i)) * X.get(i).get(j);
                }

                gradient.add(sum / m);
            }

            for (int j = 0; j < n; j++) {
                newTheta.set(j, newTheta.get(j) - alpha * gradient.get(j));
            }
        }

        return newTheta;
    }
 public static void main(String[] args) {
        String filePath4features = "heart_failure_clinical_records_dataset_cleaned.csv";
        String filePath_age_serum_sodium = "heart_failure_clinical_records_dataset_cleaned_serum_sodium.csv";
        String filePath_age_serum_creatinine = "heart_failure_clinical_records_dataset_cleaned_serum_creatinine.csv";
        String filePath_age_ejection_fraction = "heart_failure_clinical_records_dataset_cleaned_ejection_fraction.csv";
        String csvSplitBy = ",";
        String line = "";



        try (BufferedReader br = new BufferedReader(new FileReader(filePath4features))) {

            while ((line = br.readLine()) != null) {
        
                String[] filePath4features_data = line.split(csvSplitBy);
        
                // Process the data here
        
            }
        
        } catch (IOException e) {
            e.printStackTrace();
        }
        try (BufferedReader br = new BufferedReader(new FileReader(filePath_age_serum_sodium))) {

            while ((line = br.readLine()) != null) {
        
                String[] filePath_age_serum_sodium_data = line.split(csvSplitBy);
        
                // Process the data here
        
            }
        
        } catch (IOException e) {
            e.printStackTrace();
        }
        try (BufferedReader br = new BufferedReader(new FileReader(filePath_age_serum_creatinine))) {

            while ((line = br.readLine()) != null) {
        
                String[] filePath_age_serum_creatinine_data = line.split(csvSplitBy);
        
                // Process the data here
        
            }
        
        } catch (IOException e) {
            e.printStackTrace();
        }
        try (BufferedReader br = new BufferedReader(new FileReader(filePath_age_ejection_fraction))) {

            while ((line = br.readLine()) != null) {
        
                String[] filePath_age_ejection_fraction_data = line.split(csvSplitBy);
        
                // Process the data here
        
            }
        
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("The Code ran");
    }
}
