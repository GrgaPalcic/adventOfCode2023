#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char *name;
    int value;
} Pair;

typedef struct {
    int min;
    int max;
    char num[3];
}Number;


Pair pairs[] = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};


int main(int argc, char* argv[]) {
    // Check if the file path is provided as a command-line argument
    if (argc < 2) {
        printf("Please provide the file path as a command-line argument.\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[100];
    int sum = 0;

    // Read the file line by line until EOF
    while (fgets(line, sizeof(line), file) != NULL) {
        
        // Process the line here

        Number number = {
            .min = 100,
            .max = -1,
            .num = {'\0', '\0', '\0'}
        };

        for(int i = 0; i < 9; i++) {
            char* ptr = strstr(line, pairs[i].name);
            while(ptr != NULL) {
                int pos = ptr - line;
                if (pos > number.max)
                {
                    number.max = pos;
                    number.num[1] = pairs[i].value+48;
                }
                if (pos < number.min)
                {
                    number.min = pos;
                    number.num[0] = pairs[i].value+48;
                }
                ptr = strstr(ptr+1, pairs[i].name);
            }
        }
        for(int i = 0; i < 9; i++) {
            char* ptr = strchr(line, (char)(pairs[i].value+48));
            while(ptr != NULL) {
                int pos = ptr - line;
                
                //printf("Pos: %d\n", pos);
                if (pos > number.max)
                {
                    number.max = pos;
                    number.num[1] = pairs[i].value+48;
                }
                if (pos < number.min)
                {
                    number.min = pos;
                    number.num[0] = pairs[i].value+48;
                }
                ptr = strchr(ptr+1, (char)(pairs[i].value+48));
            }
        }
        
        sum += atoi(number.num);
        
    }

    printf("\nSum: %d\n", sum);

    // Close the file
    fclose(file);

    return 0;
}