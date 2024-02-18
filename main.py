import sys
import os
import math

EPSILON = 0.001

def distance(x, y):
    sum = 0
    for i in range(len(x)):
        sum += (float(x[i]) - float(y[i]))**2
    
    return math.sqrt(sum)

def isBiggerThanEpsilon(arr):
    return any([arr[i] > EPSILON for i in range(len(arr))])

def main():
    
    k = int(sys.argv[1])
    assert 1 < k, "Invalid number of clusters!"

    iter = int(sys.argv[2]) # TODO: if not provided set to 200!
    assert 1 < iter and iter < 1000, "Invalid maximum iteration!"

    file_name = sys.argv[3]
    script_dir = os.path.dirname(__file__)
    file_path = os.path.join(script_dir, file_name)
    text_file = open(file_path, 'r')
    raw_text = text_file.read()
    data_points = raw_text.splitlines()
    data_points_arr = []
    for point in data_points:
        data_points_arr.append(point.split(','))

    dimension = len(data_points_arr[0])

    # 1 - initialize centroids as first k datapoints
    centroids = [data_points_arr[i] for i in range(k)]
    
    closest_centroid_for_point = [0 for _ in range(len(data_points_arr))]
    for point_index in range(len(data_points_arr)):
        min_distance = distance(data_points_arr[point_index], centroids[0])
        for centroid_index in range(len(centroids)):
            d = distance(data_points_arr[point_index], centroids[centroid_index])
            if (d < min_distance):
                closest_centroid_for_point[point_index] = centroid_index
                min_distance = d
    
    iteration = 0
    delta_centroids = [1 for _ in range(k)]
    while ((isBiggerThanEpsilon(delta_centroids)) and (iteration < iter)):

        # 3 Assign every point to the closest cluster
        for point_index in range(len(data_points_arr)):
            closest_centroid_distance = distance(data_points_arr[point_index], centroids[closest_centroid_for_point[point_index]])
            for centroid_index in range(len(centroids)):
                d = distance(data_points_arr[point_index], centroids[centroid_index])
                if (d < closest_centroid_distance):
                    closest_centroid_for_point[point_index] = centroid_index
                    closest_centroid_distance = d

        # 4 Update the centroids
        for centroid_index in range(len(centroids)):
            sum = [0 for _ in range(dimension)]
            count = 0
            
            for i in range(len(data_points_arr)):
                if (closest_centroid_for_point[i] == centroid_index):
                    count += 1
                    for j in range(dimension):
                        sum[j] += float(data_points_arr[i][j])
                
            new_centroid = [(sum[i] / count) for i in range(dimension)]

            delta_centroids[centroid_index] = distance(centroids[centroid_index], new_centroid)
            centroids[centroid_index] = new_centroid

        iteration += 1

    # print rounded
    for centroid in centroids:
        for i in range(len(centroid)):
            if i < len(centroid) - 1:
                print(str(round(centroid[i], 4)) + ",", end="")
            else:
                print(str(round(centroid[i], 4)))

    return


if __name__ == "__main__":
    main()