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

    public static double[] train(double[][] x, double[] y, double learningRate, int numIterations) {
        int numRows = x.length;
        int numFeatures = x[0].length;
        
        double[] weights = new double[numFeatures];
        Arrays.fill(weights, 0.0);

        for (int iteration = 0; iteration < numIterations; iteration++) {
            double[] gradient = new double[numFeatures];
            Arrays.fill(gradient, 0.0);

            for (int i = 0; i < numRows; i++) {
                double predictedProbability = predictProbability(x[i], weights);
                for (int j = 0; j < numFeatures; j++) {
                    gradient[j] += (predictedProbability - y[i]) * x[i][j];
                }
            }

            for (int j = 0; j < numFeatures; j++) {
                weights[j] -= learningRate * gradient[j] / numRows;
            }
        }

        return weights;
    }
    private static double sigmoid(double z) {
        return 1.0 / (1.0 + Math.exp(-z));
    }

    private static double predictProbability(double[] x, double[] weights) {
        double z = 0.0;
        for (int i = 0; i < x.length; i++) {
            z += x[i] * weights[i];
        }
        return sigmoid(z);
    }

    public static double calculateLogLoss(List<Double> predictedProbabilities, double[] actualLabels) {
        double logLoss = 0.0;
        for (int i = 0; i < predictedProbabilities.size(); i++) {
            double p = predictedProbabilities.get(i);
            double y = actualLabels[i];
            logLoss += y * Math.log(p) + (1 - y) * Math.log(1 - p);
        }
        return -logLoss / predictedProbabilities.size();
    }
    

    public static void unitVectorNormalize(double[][] X) {
        
        int numFeatures = X[1].length;
        double[] minValues = new double[numFeatures];
        double[] maxValues = new double[numFeatures];
        
        for (int j = 1; j < numFeatures; j++) {
            double min = Double.MAX_VALUE;
            double max = Double.MIN_VALUE;
            for (int i = 0; i < X.length; i++) {
                double value = X[i][j];
                if (value < min) {
                    min = value;
                }
                if (value > max) {
                    max = value;
                }
            }
            minValues[j] = min;
            maxValues[j] = max;
        }
        
        // Step 2: Normalize the data
        for (int i = 0; i < X.length; i++) {
            for (int j = 1; j < numFeatures; j++) {
                double value = X[i][j];
                double range = maxValues[j] - minValues[j];
                double normalized = (value - minValues[j]) / range;
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
        double learningRate = 0.001;
        int numIterations = 100000;

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
        
        for (int i = 0; i < XTrain.length; i++) {
            for (int j = 0; j < XTrain[i].length; j++) {
                //System.out.print(XTrain[i][j] + " ");
            }
            //System.out.println();
        }
       // System.out.println("xtrain" + XTrain);
        //System.out.println("ytrain" + yTrain);

        System.out.println("Training the model...");
        double[] weights = train(XTrain, yTrain, learningRate, numIterations);
        System.out.println("Weights have been trained: " + Arrays.toString(weights));

        List<Double> predictedTrain = new ArrayList<>();
for (double[] row : XTrain) {
    double prediction = predictProbability(row, weights);
    predictedTrain.add(prediction);
}
double trainLogLoss = calculateLogLoss(predictedTrain, yTrain);
System.out.println("Training log loss: " + trainLogLoss);

// Evaluate the test data
List<Double> predictedTest = new ArrayList<>();
for (double[] row : XTest) {
    double prediction = predictProbability(row, weights); // Use predictProbability instead of dotProduct
    predictedTest.add(prediction);
}

// Calculate the log loss for the test set
double testLogLoss = calculateLogLoss(predictedTest, yTest);
System.out.println("Test log loss: " + testLogLoss);
System.out.println("learning rate:"+ learningRate);
System.out.println("number of iterations:"+ numIterations);


        if (x.length == 0) {
            System.out.println("No data found in the CSV file.");
            return;
        }
    }
}


