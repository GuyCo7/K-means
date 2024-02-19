#include <stdio.h>
#include <stdlib.h>

int EPSILON = 0.001;

int main(int argc, char **argv)
{

    int k;
    int iter;
    char *file_name;
    FILE *fptr;
    int ch;
    int tokenCount = 0;
    double *point = NULL;
    char *token = NULL;
    double **data_points_arr = NULL;
    int data_points_length = 0;

    if (argc > 4)
    {
        return 1;
    }

    if (argc == 4)
    {
        iter = atoi(argv[2]);
        file_name = argv[3];
    }
    else if (argc == 3)
    {
        iter = 200;
        file_name = argv[2];
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

    fptr = fopen(file_name, "r");

    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == ',' || ch == '\n')
        {
            tokenCount++;
            point = realloc(point, tokenCount * sizeof(double));
            point[tokenCount - 1] = atof(token);
            free(token);
            token = NULL;

            if (ch == '\n')
            {
                data_points_arr = realloc(data_points_arr, (data_points_length + 1) * sizeof(double *));
                data_points_arr[data_points_length] = point;

                tokenCount = 0;
                point = NULL;
                data_points_length++;
            }
        }
        else
        {
            token = realloc(token, (tokenCount + 1) * sizeof(char));
            token[tokenCount - 1] = ch;
            tokenCount++;
        }
    }

    printf("length --- %d", data_points_length);

    fclose(fptr);

    k = atoi(argv[1]);
    if (k < 1 || k > data_points_length)
    {
        printf("Invalid number of clusters!");
    }

    printf("Data Points:\n");
    for (int i = 0; i < data_points_length; i++)
    {
        printf("Point %d: (", i + 1);
        for (int j = 0; j < 3; j++)
        {
            printf("%.2lf", data_points_arr[i][j]);
            if (j < 3 - 1)
            {
                printf(", ");
            }
        }
        printf(")\n");
    }

    for (int i = 0; i < data_points_length; i++)
    {
        free(data_points_arr[i]);
    }
    free(data_points_arr);

    return 0;
}