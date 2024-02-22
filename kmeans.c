#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.001
#define DEFAULT_ITERATIONS 200
#define MAX_ITERATIONS 1000

double distance(double *point1, double *point2, int d);
int areBiggerThanEpsilon(double *arr, int size);
int is_integer(char *str);

int main(int argc, char **argv)
{
    int k, n, d, iter;
    double **vectors_arr;
    int i, j;
    int count = 0;
    double **centroids;
    int *closest_centroid_for_vector;
    int iteration = 0;
    double *delta_centroids;
    int point_index;
    double closest_centroid_distance;
    int centroid_index;
    double curr_d;
    double *sum;
    double *new_centroid;

    if (argc != 4 && argc != 5)
    {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    if (!(is_integer(argv[1])))
    {
        printf("Invalid number of clusters!\n");
        return 1;
    }
    if (!(is_integer(argv[2])))
    {
        printf("Invalid number of points!\n");
        return 1;
    }
    if (!(is_integer(argv[3])))
    {
        printf("Invalid dimension of point!\n");
        return 1;
    }
    if (atoi(argv[1]) > 1 && atoi(argv[1]) < atoi(argv[2]))
    {
        k = atoi(argv[1]);
    }
    else
    {
        printf("Invalid number of clusters!\n");
        return 1;
    }
    if (atoi(argv[2]) > 1)
    {
        n = atoi(argv[2]);
    }
    else
    {
        printf("Invalid number of points!\n");
        return 1;
    }
    if (atoi(argv[3]) >= 1)
    {
        d = atoi(argv[3]);    
    }
    else
    {
        printf("Invalid dimension of point!\n");
        return 1;
    }
    if (argc == 4)
    {
        iter = DEFAULT_ITERATIONS;
    }
    else
    {
        if (!(is_integer(argv[4])))
        {
            printf("Invalid maximum iteration!\n");
            return 1;
        }
        if (atoi(argv[4]) > 1 && atoi(argv[4]) < MAX_ITERATIONS)
        {
            iter = atoi(argv[4]);
        }
        else
        {
            printf("Invalid maximum iteration!\n");
            return 1;
        }
    }

    /* Allocate memory for vectors */
    vectors_arr = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        vectors_arr[i] = (double *)malloc(d * sizeof(double));
        for (j = 0; j < d; j++)
        {
            scanf("%lf,", &vectors_arr[i][j]);
        }
    }

    /* Allocate memory for centroids */
    centroids = (double **)malloc(k * sizeof(double *));
    for (i = 0; i < k; i++)
    {
        centroids[i] = (double *)malloc(d * sizeof(double));
        for (j = 0; j < d; j++)
        {
            centroids[i][j] = vectors_arr[i][j];
        }
    }

    closest_centroid_for_vector = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        double min_distance = distance(vectors_arr[i], centroids[0], d);
        closest_centroid_for_vector[i] = 0;
        for (j = 1; j < k; j++)
        {
            double curr_distance = distance(vectors_arr[i], centroids[j], d);
            if (curr_distance < min_distance)
            {
                closest_centroid_for_vector[i] = j;
                min_distance = curr_distance;
            }
        }
    }

    delta_centroids = (double *)malloc(k * sizeof(double));
    for (i = 0; i < k; i++)
    {
        delta_centroids[i] = 1.0;
    }

    sum = (double *)malloc(d * sizeof(double));
    for (i = 0; i < d; i++)
    {
        sum[i] = 0.0;
    }

    new_centroid = (double *)malloc(d * sizeof(double));
    for (i = 0; i < d; i++)
    {
        new_centroid[i] = 0.0;
    }

    while (areBiggerThanEpsilon(delta_centroids, k) && iteration < iter)
    {
        for (point_index = 0; point_index < n; point_index++)
        {
            closest_centroid_distance = distance(vectors_arr[point_index], centroids[closest_centroid_for_vector[point_index]], d);
            for (centroid_index = 0; centroid_index < k; centroid_index++)
            {
                curr_d = distance(vectors_arr[point_index], centroids[centroid_index], d);
                if (curr_d < closest_centroid_distance)
                {
                    closest_centroid_for_vector[point_index] = centroid_index;
                    closest_centroid_distance = curr_d;
                }
            }
        }
        for (centroid_index = 0; centroid_index < k; centroid_index++)
        {
            for (i = 0; i < d; i++)
            {
                sum[i] = 0.0;
            }
            for (i = 0; i < d; i++)
            {
                new_centroid[i] = 0.0;
            }
            count = 0;
            for (i = 0; i < n; i++)
            {
                if (closest_centroid_for_vector[i] == centroid_index)
                {
                    count++;
                    for (j = 0; j < d; j++)
                    {
                        sum[j] += vectors_arr[i][j];
                    }
                }
            }
            for (j = 0; j < d; j++)
            {
                new_centroid[j] = sum[j] / count;
            }
            delta_centroids[centroid_index] = distance(centroids[centroid_index], new_centroid, d);
            for (i = 0; i < d; i++)
            {
                centroids[centroid_index][i] = new_centroid[i];
            }
        }
        iteration++;
    }

    /* Print centroids */
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < d; j++)
        {
            printf("%.4f", centroids[i][j]);
            if (j < d - 1)
            {
                printf(",");
            }
            else
            {
                printf("\n");
            }
        }
    }

    /* Free allocated memory */
    for (i = 0; i < k; i++)
    {
        free(centroids[i]);
    }
    free(centroids);
    free(closest_centroid_for_vector);
    free(delta_centroids);
    free(sum);
    free(new_centroid);
    for (i = 0; i < n; i++)
    {
        free(vectors_arr[i]);
    }
    free(vectors_arr);

    return 0;
}

double distance(double *point1, double *point2, int d)
{
    double sum = 0.0;
    int i;
    for (i = 0; i < d; i++)
    {
        sum += pow(point1[i] - point2[i], 2);
    }
    return sqrt(sum);
}

int areBiggerThanEpsilon(double *arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] > EPSILON)
        {
            return 1;
        }
    }
    return 0;
}

int is_integer(char *str)
{
    char *endptr;
    strtol(str, &endptr, 10);
    if (*endptr != '\0' || endptr == str)
    {
        return 0;
    }
    return 1;
}
