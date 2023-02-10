dataset = [[5.1,3.5,1.4,1],[6.9,3.2,5.7,-1],[4.7,3.2,1.3,1],
    [4.6,3.1,1.5,1],[5,3.6,1.4,1],[5.7,2.5,5.0,-1],
    [4.9,2.5,4.5,-1],[6.0,2.2,5.0,-1],[4.4,2.9,1.4,1]]
bias = 1
threshold = 0
weights = [0,0,0]
output = 0
iteratorMAX = 1000




for iterator in range(iteratorMAX):
    hits = 0
    for x in range(0,len(dataset)):
        Weightedsum = 0
        for z in range(0,len(dataset[x])-1):
            Weightedsum += dataset[x][z] * weights[z]
            #this matches the weights and array values
        output = bias + Weightedsum
        if output < threshold:
            output = 1
        else:
            output = -1
    if output != dataset[x][2]:
        for z in range(0, len(weights)):
            weights[z] += (dataset[x][2] * dataset[x][z])
        bias += dataset[x][2]

    else:
        hits = hits +1

print(weights)
        
    
