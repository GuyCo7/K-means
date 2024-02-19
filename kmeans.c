#include <stdio.h>
#include <stdlib.h>

#define EPSILON = 0.001;

int main(int argc, char **argv)
{
    int k;
    int N;
    int d;
    int iter;
    char *file_name;
    FILE *fptr;
    float data_points_arr[N][d];

    k = atoi(argv[1]);
    N = atoi(argv[2]);
    d = atoi(argv[3]);
    iter = atoi(argv[4]);
    file_name = argv[5];


    if (k < 1 || k > N)
    {
        printf("Invalid number of clusters!");
        return 1;
    }

    if (argc > 6)
    {
        return 1;
    }

    if (argc == 6)
    {
        iter = atoi(argv[4]);
        file_name = argv[5];
    }
    else if (argc == 5)
    {
        iter = 200;
        file_name = argv[4];
    }
    else
    {
        return 1;
    }

    if (iter < 1 || iter > 1000)
    {
        printf("Invalid maximum iteration!");
        return 1;
    }

    printf("Trying to open");

    fptr = fopen(file_name, "r");

    printf("Opened");

    float value;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < d; j++)
        {
            scanf("%lf,", &value);
            data_points_arr[i][j] = value;
        }
    }

    fclose(fptr);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%.4lf", data_points_arr[i][j]);
            if (j < d - 1)
            {
                printf(", ");
            }
        }
        printf("\n");
    }

    // free data points allocation
    // for (int i = 0; i < data_points_length; i++)
    // {
    //     free(data_points_arr[i]);
    // }
    // free(data_points_arr);

    return 0;
}