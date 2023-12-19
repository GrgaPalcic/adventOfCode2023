#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DATA_SIZE 142

typedef struct {
    bool valid;
    int a;
    int b;
} Gear;

Gear check_surrounding(int row, int column, char data[DATA_SIZE][DATA_SIZE])
{
    Gear gear = {false, 0, 0};

    for (int i = row-(row > 0 ? 1 : 0); i <= row+(row < DATA_SIZE-3 ? 1 : 0); i++){
        for(int j = column-(column > 0 ? 1 : 0); j <= column+1 - (column+1 < DATA_SIZE-2 ? 0 : 1); j++){
            
            char *ptr = &data[i][j];
            char *tmp = ptr;

            if (data[i][j] != '*' && isdigit(data[i][j])) {
                int tmp_j = j;
                while(isdigit(data[i][tmp_j]) || data[i][tmp_j] == '-') tmp_j--;
                tmp_j++;

                if(gear.a > 0){
                    gear.b = strtol(tmp-(j-tmp_j), &ptr, 10);
                    j = j + (ptr - tmp);
                    gear.valid = true;
                }
                else if(gear.a == 0){
                    gear.a = strtol(tmp-(j-tmp_j), &ptr, 10);
                    j = j + (ptr - tmp);
                }else
                    gear.valid = false;
            }
        }
    }
    return gear;
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
    int ref = 0;
    int ref_nv = 0;
    for (int i = 0; i < row; i++)
    {

        int ptr = 0;
        while (data[i][ptr] != '\0'){

            if(data[i][ptr] == '*'){
                Gear gear = check_surrounding(i, ptr, data);
                sum += gear.a * gear.b;
                printf("Gear: %d, %d Valid: %d\n", gear.a, gear.b, gear.valid);
                ref++;
                if(!gear.valid) ref_nv++;
            }
            ptr++;

        }
    }

    printf("Sum of all engine parts: %d, %d, %d\n", sum, ref, ref_nv);
    

    // Close the file
    fclose(file);

    return 0;
}
