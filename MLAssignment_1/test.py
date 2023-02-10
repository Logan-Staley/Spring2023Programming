

input = [(6.2,2.2,1), (5.6,2.5,-1), (5.8,3,-1), (6.3,2.7,1), (6.3,2.5,1), (6.2,2.8,1), (6.4,2.9,1), (6.6,3.0,1), 
         (6.6,2.8,1), (6.7,3.0,1), (6.0,2.5,1), (5.7,2.6,-1), (5.5,2.4,-1), (5.5,2.9,-1), (5.8,2.7,-1), (6.2,2.7,1), 
         (5.4,3.0,-1), (5.6,2.8,-1), (5.7,3.1,-1), (5.5,2.5,-1), (5.9,3,-1),(5.9,2.6,1)]

threshold = 0        #Variable declarations
weights = [0,0]
bias = 1
y=0
maxIterator = 10000
    
    
for iterator in range(maxIterator):
    hits = 0
    
    for i in range(0, len(input)):        #Iterates through the array
        weightedSum = 0
        
        for j in range(0,len(input[i])-1):        #Calculates weightedSum by iterating through the array
            weightedSum += input[i][j] * weights[j]
            
        output = bias + weightedSum
     
        if output > threshold:        #Assigns y value to find if a point is misclassified
            y = 1
        else:
            y = -1
        
        if y != input[i][2]:        #Determines if a point is misclassified 
            for j in range(0, len(weights)):
                weights[j] += (input[i][2] * input[i][j])
                
            bias += input[i][2]
            
        else:
            hits = hits + 1

    
    if hits == len(input):        #Returns the best weight for the dataset
        print("The best weight that was found is: ", weights)
        break;        #Breaks the loop