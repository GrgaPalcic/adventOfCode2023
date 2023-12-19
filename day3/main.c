#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DATA_SIZE 142

bool check_surrounding(int row, int first_i, int num_len, char data[DATA_SIZE][DATA_SIZE])
{
    for (int i = row-(row > 0 ? 1 : 0); i <= row+(row < DATA_SIZE-3 ? 1 : 0); i++){
        for(int j = first_i-(first_i > 0 ? 1 : 0); j <= first_i+num_len-(first_i+num_len < DATA_SIZE-2 ? 0 : 1); j++){
            if (data[i][j] != '.' && isdigit(data[i][j]) == 0) return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    // Check if the file path is provided as a command-line argument
    if (argc < 2)
    {
        printf("Please provide the file path as a command-line argument.\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[DATA_SIZE];
    char data[DATA_SIZE][DATA_SIZE];
    int row = 0;
    int sum = 0;

    // Read the file line by line until EOF
    while (fgets(line, sizeof(line), file) != NULL)
    {
        strcpy(data[row], line);
        data[row][strlen(line)] = '\0';
        row++;
    }

    for (int i = 0; i < row; i++)
    {
        char *ptr = data[i];
        while (*ptr != '\0')
        {
            char *tmp = ptr;
            int num = strtol(ptr, &ptr, 10);
            if (num != 0){

                if(check_surrounding(i, tmp - data[i], ptr - tmp, data))
                    sum += labs(num);
                
                ptr++;
                continue;
            }
            ptr++;
        }
    }

    printf("Sum of all engine parts: %d\n", sum);
    

    // Close the file
    fclose(file);

    return 0;
}
