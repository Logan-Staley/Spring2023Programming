package Termproject.logistic;

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

public class Heart_failure_Test {

    public static double[] train(double[][] X, double[] y, double learningRate, int numIterations) {
        int m = X.length;
        int n = X[0].length;
        double[] weights = new double[n];
        Random rand = new Random();

        // Initialize the weights with random values between -0.1 and 0.1
        for (int i = 0; i < n; i++) {
            weights[i] = -0.1 + rand.nextDouble() * 0.2;
        }

        for (int iteration = 0; iteration < numIterations; iteration++) {
            // Compute the predicted values using the sigmoid function
            double[] predicted = new double[m];
            for (int i = 0; i < m; i++) {
                double sum = 0.0;
                for (int j = 0; j < n; j++) {
                    sum += X[i][j] * weights[j];
                }
                double probability = sigmoid(sum);
                predicted[i] = probability;
            }

            // Compute the error
            double[] error = new double[m];
            for (int i = 0; i < m; i++) {
                error[i] = predicted[i] - y[i];
            }

            // Compute the gradient
            double[] gradient = new double[n];
            for (int j = 0; j < n; j++) {
                double sum = 0.0;
                for (int i = 0; i < m; i++) {
                    sum += X[i][j] * error[i];
                }
                gradient[j] = sum / m;
            }

            // Update the weights
            for (int j = 0; j < n; j++) {
                weights[j] = weights[j] - learningRate * gradient[j];
            }

            // Compute the cost function
            double cost = 0.0;
            for (int i = 0; i < m; i++) {
                double predictedY = predicted[i];
                double actualY = y[i];
                cost += actualY * Math.log(predictedY) + (1 - actualY) * Math.log(1 - predictedY);
            }
            cost /= (-1.0 * m);

            // Check if the cost function is below a certain threshold
            if (cost < 0.0001) {
                break;
            }
        }

        return weights;
    }

    private static double sigmoid(double z) {
        return 1.0 / (1.0 + Math.exp(-z));
    }

    public static void unitVectorNormalize(double[][] X) {
        int numExamples = X.length;
        int numFeatures = X[0].length;

        // Compute the magnitude of each row
        double[] magnitudes = new double[numExamples];
        for (int i = 0; i < numExamples; i++) {
            double sumSquares = 0.0;
            for (int j = 0; j < numFeatures; j++) {
                double value = X[i][j];
                sumSquares += value * value;
            }
            double magnitude = Math.sqrt(sumSquares);
            magnitudes[i] = magnitude;
        }

        // Normalize each row in X
        for (int i = 0; i < numExamples; i++) {
            double magnitude = magnitudes[i];
            for (int j = 0; j < numFeatures; j++) {
                double value = X[i][j];
                double normalized = value / magnitude;
                X[i][j] = normalized;
            }
        }
    }

    public static boolean isNormalized(double[][] data) {
        int numFeatures = data[0].length;

        // Check the mean and standard deviation for each feature
        for (int j = 1; j < numFeatures; j++) {
            double sum = 0.0;
            double sumSquares = 0.0;
            for (int i = 0; i < data.length; i++) {
                double value = data[i][j];
                sum += value;
                sumSquares += value * value;
            }
            double mean = sum / data.length;
            double variance = (sumSquares / data.length) - (mean * mean);
            double stdDev = Math.sqrt(variance);

            // Check that the mean is close to 0 and the standard deviation is close to 1
            if (Math.abs(mean) > 0.01 || Math.abs(stdDev - 1.0) > 0.01) {
                return false;
            }
        }

        return true;
    }

    public static double dotProduct(double[] rowArray, double[] doubles) {
        double result = 0.0;
        for (int i = 0; i < rowArray.length; i++) {
            result += rowArray.length * doubles.length;
        }
        return result;
    }


    public static void main(String[] args) {
        String filePath4features = "Termproject/logistic/heart_failure_clinical_records_dataset_cleaned.csv";
        /// String filePath_age_serum_sodium =
        /// "heart_failure_clinical_records_dataset_cleaned_serum_sodium.csv";
        // String filePath_age_serum_creatinine =
        /// "heart_failure_clinical_records_dataset_cleaned_serum_creatinine.csv";
        // String filePath_age_ejection_fraction =
        /// "heart_failure_clinical_records_dataset_cleaned_ejection_fraction.csv";
        String csvSplitBy = ",";
        String line = "";
        System.out.println("Reading CSV file: " + filePath4features);
        double[][] x = new double[0][0];
        double[] y = new double[0];
        double learningRate = 0.1;
        int numIterations = 1000;

        // variables declared ^^^^^

        try (BufferedReader br = new BufferedReader(new FileReader(filePath4features))) {
            String headerLine = br.readLine();
            
            // System.out.println("Header: " + headerLine);
            int numFeatures = headerLine.split(csvSplitBy).length - 1;
            List<double[]> XList = new ArrayList<>();
            List<Double> yList = new ArrayList<>();
            while ((line = br.readLine()) != null) {
                String[] fields = line.split(csvSplitBy);

                // Convert the fields to doubles and add them to the X list
                double[] row = new double[numFeatures + 1]; // Add one for the bias term
                row[0] = 1.0; // Add a bias term of 1.0
                for (int i = 0; i < numFeatures; i++) {
                    row[i + 1] = Double.parseDouble(fields[i]);
                }
                yList.add(Double.parseDouble(fields[numFeatures]));
                XList.add(row);

            }

            // Convert the list of arrays to a 2D array
            x = XList.toArray(new double[XList.size()][]);
            y = yList.stream().mapToDouble(Double::doubleValue).toArray();
        } catch (IOException e) {
            e.printStackTrace();
        }

        int numExamples = x.length;
        int numTrainExamples = (int) (0.8 * numExamples);
        double[][] XTrain = Arrays.copyOfRange(x, 0, numTrainExamples);
        double[] yTrain = Arrays.copyOfRange(y, 0, numTrainExamples);
        double[][] XTest = Arrays.copyOfRange(x, numTrainExamples, numExamples);
        double[] yTest = Arrays.copyOfRange(y, numTrainExamples, numExamples);

        System.out.println("The Code ran");

        unitVectorNormalize(XTrain);
        unitVectorNormalize(XTest);

        System.out.println("Training the model...");
        double[] weights = train(XTrain, yTrain, learningRate, numIterations);
        System.out.println("Weights have been trained: " + Arrays.toString(weights));

        if (x.length == 0) {
            System.out.println("No data found in the CSV file.");
            return;
        }
    }
}


