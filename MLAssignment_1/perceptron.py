import numpy as np

class PerceptronClass:
    dataset = np.array[[5.1,3.5,1.4,0.2],[4.9,3,1.4,0.2],[4.7,3.2,1.3,0.2],
    [4.6,3.1,1.5,0.2],[5,3.6,1.4,0.2],[5.4,3.9,1.7,0.4],
    [4.6,3.4,1.4,0.3],[5,3.4,1.5,0.2],[4.4,2.9,1.4,0.2]]


    def __init__(self, learning_rate=0.01, iterations=1000):
        self.weights = None
        self.bias = None
        self.num_iterations = iterations
        self.lr = learning_rate

    def _unit_step_func(self, dataset):
        return np.where(dataset >= 0, 1, 0)


#this function will provide parameters randomly along with weights and biases.
#then predict an output and then apply an update function to the weights and biases
#as it passes throught the matrix.

    def arrange(self, dataset, y):
        n_samples, n_features = dataset.shape

        #init parameters
        self.weights = np.zeros(n_features)
        self.bias = 0
        y_ = np.array([1 if i > 0 else 0 for i in y])

        #loop that will update the weights for each value in the matrix
        for b in range(self.num_iterations):
            
            for index, x_i in enumerate(dataset):

                linearout = np.dot(x_i,self.weights) + self.bias

                #predicted values to be updated 
                y_predicted = self._unit_step_func(linearout)
                
                update = self.lr * (y_predicted * y_[index])

                #update the weights
                self.weights -= update * x_i
                self.bias -= update
def predict(self,X):
    linear_out = np.dot(X,self.weights) + self.bias
    y_predicted = self._unit_step_func(linear_out)
    return y_predicted
                



perceptron = PerceptronClass()

y_predicted = perceptron.predict(dataset)