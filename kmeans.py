import sys
import math

EPSILON = 0.001

def main():

    # In case of extra/less arguments
    if (len(sys.argv) < 5 or len(sys.argv) > 6):
        print("Please Enter 4 or 5 arguments")
        exit()

    k = int(sys.argv[1])
    n = int(sys.argv[2])
    d = int(sys.argv[3])
    
    if (sys.argv[4].isdigit()):
        iter = int(sys.argv[4])
        file_name = sys.argv[5]
    else:
        # if iter is not provided
        iter = 200
        file_name = sys.argv[4]

    # Validation of the arguments
    assert n > 1, "Invalid number of points!"
    assert k > 1 and k < n, "Invalid number of clusters!"
    assert d > 1, "Invalid dimension of point!"
    assert iter > 1 and iter < 1000, "Invalid maximum iteration!"

    # Reading from file
    text_file = open(file_name, 'r')
    raw_text = text_file.read()
    text_file.close()

    # Manipulation on the data (splitting by new lines and then by comma)
    vectors = raw_text.splitlines()
    vectors_arr = [vector.split(',') for vector in vectors]

    # Step 1: Initialize first k vectors as centroids
    centroids = [vectors_arr[i] for i in range(k)]
    
    # Steps 2&5: Iterate until all delta centroids are smaller than EPSILON or max iteration is reached
    iteration = 0
    delta_centroids = [1 for _ in range(k)]
    while are_bigger_than_epsilon(delta_centroids) and iteration < iter:

        # Step 3: Assign every vector to the closest cluster 
        closest_centroid_for_vector = find_closest_centroids(vectors_arr, centroids)

        # Step 4: Update the centroids
        for centroid_index in range(k):
            sum = [0 for _ in range(d)]
            count = 0
            
            for i in range(n):
                if closest_centroid_for_vector[i] == centroid_index:
                    count += 1
                    for j in range(d):
                        sum[j] += float(vectors_arr[i][j])
                
            new_centroid = [(sum[i] / count) for i in range(d)]

            delta_centroids[centroid_index] = euclidean_distance(centroids[centroid_index], new_centroid)
            centroids[centroid_index] = new_centroid

        iteration += 1


    # Print centroids
    for centroid in centroids:
        formatted_centroid = ",".join(["{:.4f}".format(coordination) for coordination in centroid])
        print(formatted_centroid)

    return


# Function to find closest centroids for each vector
def find_closest_centroids(vectors_arr, centroids):
    closest_centroid_for_vector = []
    for vector in vectors_arr:
        distances = [euclidean_distance(vector, centroid) for centroid in centroids]
        closest_centroid_for_vector.append(distances.index(min(distances)))
    return closest_centroid_for_vector

# Function to calculate Euclidean distance
def euclidean_distance(vector_x, vector_y):
    sum = 0
    for i in range(len(vector_x)):
        sum += (float(vector_x[i]) - float(vector_y[i])) ** 2
    
    return math.sqrt(sum)

# Function to check if any value in the array is bigger than EPSILON
def are_bigger_than_epsilon(arr):
    return any(value > EPSILON for value in arr)


if __name__ == "__main__":
    main()
