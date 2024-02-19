import sys
import math

EPSILON = 0.001

def main():
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
    assert 1 < n, "Invalid number of points!"
    assert 1 < k and k < n, "Invalid number of clusters!"
    assert 1 < d, "Invalid dimension of point!"
    assert 1 < iter and iter < 1000, "Invalid maximum iteration!"

    # Reading from file
    text_file = open(file_name, 'r')
    raw_text = text_file.read()

    # Manipulation on the data
    vectors = raw_text.splitlines()
    vectors_arr = [vector.split(',') for vector in vectors]

    # 1 - initialize first k vectors as centroids
    centroids = [vectors_arr[i] for i in range(k)]
    
    closest_centroid_for_vector = find_closest_centroids(vectors_arr, centroids, n, k)
    
    iteration = 0
    delta_centroids = [1 for _ in range(k)]
    while ((are_bigger_than_epsilon(delta_centroids)) and (iteration < iter)):

        # 3 Assign every vector to the closest cluster
        for vector_index in range(n):
            closest_centroid_distance = euclidean_distance(vectors_arr[vector_index], centroids[closest_centroid_for_vector[vector_index]])
            for centroid_index in range(k):
                distance = euclidean_distance(vectors_arr[vector_index], centroids[centroid_index])
                if (distance < closest_centroid_distance):
                    closest_centroid_for_vector[vector_index] = centroid_index
                    closest_centroid_distance = distance

        # 4 Update the centroids
        for centroid_index in range(k):
            sum = [0 for _ in range(d)]
            count = 0
            
            for i in range(n):
                if (closest_centroid_for_vector[i] == centroid_index):
                    count += 1
                    for j in range(d):
                        sum[j] += float(vectors_arr[i][j])
                
            new_centroid = [(sum[i] / count) for i in range(d)]

            delta_centroids[centroid_index] = euclidean_distance(centroids[centroid_index], new_centroid)
            centroids[centroid_index] = new_centroid

        iteration += 1


    # print rounded
    for centroid in centroids:
        for i in range(d):
            if i < (d - 1):
                print("{:.4f}".format(centroid[i]) + ",", end="")
            else:
                print("{:.4f}".format(centroid[i]))

    return


# Functions:

def find_closest_centroids(vectors_arr, centroids, n, k):
    closest_centroid_for_vector = [0 for _ in range(n)]
    for vector_index in range(n):
        min_distance = euclidean_distance(vectors_arr[vector_index], centroids[0])
        for centroid_index in range(k):
            distance = euclidean_distance(vectors_arr[vector_index], centroids[centroid_index])
            if (distance < min_distance):
                closest_centroid_for_vector[vector_index] = centroid_index
                min_distance = distance
    return closest_centroid_for_vector

def euclidean_distance(vector_x, vector_y):
    sum = 0
    for i in range(len(vector_x)):
        sum += (float(vector_x[i]) - float(vector_y[i]))**2
    
    return math.sqrt(sum)

def are_bigger_than_epsilon(arr):
    return any([arr[i] > EPSILON for i in range(len(arr))])


if __name__ == "__main__":
    main()