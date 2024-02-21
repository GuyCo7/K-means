#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.001

double distance(double *point1, double *point2, int d);
int areBiggerThanEpsilon(double *arr, int size);


int main(int argc, char **argv)
{
    int k, n, d, iter;
    double **data_points_arr;
    int i, j;
    int count=0;
    double **centroids;
    int *closest_centroid_for_point;
    int iteration = 0;
    double *delta_centroids;
    int point_index;
    double closest_centroid_distance;
    int centroid_index;
    double curr_d;
    double *sum;
    double *new_centroid;
    
    if (argc != 4 && argc != 5) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    k = atoi(argv[1]);
    n = atoi(argv[2]);
    d = atoi(argv[3]);
    iter = (argc == 4) ? 200 : atoi(argv[4]);
    
    if (k <= 1 || k >= n) {
        printf("Invalid number of clusters!\n");
        return 1;
    }
    if (n <= 1) {
        printf("Invalid number of points!\n");
        return 1;
    }
    if (d <= 0) {
        printf("Invalid dimension of point!\n");
        return 1;
    }
    if (iter <= 1 || iter >= 1000) {
        printf("Invalid maximum iteration!\n");
        return 1;
    }



    data_points_arr = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        data_points_arr[i] = (double *)malloc(d * sizeof(double));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < d; j++) {
            scanf("%lf,", &data_points_arr[i][j]);
        }
    }

    centroids = (double **)malloc(k * sizeof(double *));
    for (i = 0; i < k; i++) {
        centroids[i] = (double *)malloc(d * sizeof(double));
        for (j = 0; j < d; j++) {
            centroids[i][j] = data_points_arr[i][j];
        }
    }

    closest_centroid_for_point = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        double min_distance = distance(data_points_arr[i], centroids[0], d);
        closest_centroid_for_point[i] = 0;
        for (j = 1; j < k; j++) {
            double curr_distance = distance(data_points_arr[i], centroids[j], d);
            if (curr_distance < min_distance) {
                closest_centroid_for_point[i] = j;
                min_distance = curr_distance;
            }
        }
    }

    delta_centroids = (double *)malloc(k * sizeof(double));
    for (i = 0; i < k; i++) {
        delta_centroids[i] = 1.0;
    }

    sum = (double *)malloc(d * sizeof(double));
    for (i = 0; i < d; i++) {
        sum[i] = 0.0;
    }

    new_centroid = (double *)malloc(d * sizeof(double));
    for (i = 0; i < d; i++) {
        new_centroid[i] = 0.0;
    }

    while (areBiggerThanEpsilon(delta_centroids, k) && iteration < iter) {
        for (point_index = 0; point_index < n; point_index++) {
            closest_centroid_distance = distance(data_points_arr[point_index], centroids[closest_centroid_for_point[point_index]], d);
            for (centroid_index = 0; centroid_index < k; centroid_index++) {
                curr_d = distance(data_points_arr[point_index], centroids[centroid_index], d);
                if (curr_d < closest_centroid_distance) {
                    closest_centroid_for_point[point_index] = centroid_index;
                    closest_centroid_distance = curr_d;
                }
            }
        }
        for (centroid_index = 0; centroid_index < k; centroid_index++) {
            for (i = 0; i < d; i++) {
                sum[i] = 0.0;
            }
            for (i = 0; i < d; i++) {
                new_centroid[i] = 0.0;
            }
            count=0;
            for (i = 0; i < n; i++) {
                if (closest_centroid_for_point[i] == centroid_index) {
                    count++;
                    for (j = 0; j < d; j++) {
                        sum[j] += data_points_arr[i][j];
                    }
                }
            }
            for (j = 0; j < d; j++) {
                new_centroid[j] = sum[j] / count;
            }       
            delta_centroids[centroid_index] = distance(centroids[centroid_index], new_centroid, d);
            for (i = 0; i < d; i++) {
                centroids[centroid_index][i] = new_centroid[i];
            }
        }
        iteration++;
    }

    for (i = 0; i < k; i++) {
        for (j = 0; j < d; j++) {
            printf("%.4f", centroids[i][j]);
            if (j < d - 1) {
                printf(",");
            }
            else {
                    printf("\n");
            }
        }
    }
  

    for (i = 0; i < k; i++) {
        free(centroids[i]);
    }
    free(centroids);
    free(closest_centroid_for_point);
    free(delta_centroids);
    free(sum);
    free(new_centroid);
    for (i = 0; i < n; i++) {
        free(data_points_arr[i]);
    }
    free(data_points_arr);

    return 0;
}

double distance(double *point1, double *point2, int d) {
    double sum = 0.0;
    int i;
    for (i = 0; i < d; i++) {
        double diff = point1[i] - point2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

int areBiggerThanEpsilon(double *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] > EPSILON) {
            return 1;  
        }
    }
    return 0;  
}
