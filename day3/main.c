#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

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

    char line[142];
    char data[142][142];
    int row = 0;


    // Read the file line by line until EOF
    while (fgets(line, sizeof(line), file) != NULL)
    {
        strcpy(data[row], line);
        row++;
        
    }

    

    // Close the file
    fclose(file);

    return 0;
}