#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DATA_SIZE 142

typedef struct {
    int number;
    char info[200];
    int win_num[DATA_SIZE];
    int my_num[DATA_SIZE];
    int win;
} Card;

void extractNumbers(char *inputString, int *firstArray, int *secondArray) {
  
    char *saveptr, *saveptr2;
    char *token = strtok_r(inputString, "|", &saveptr);

    token = strtok_r(token, " ", &saveptr2);
    int i = 0;
    while (token != NULL) {
        if (isdigit(token[0])) {
            firstArray[i++] = atoi(token);
        }
        token = strtok_r(NULL, " ", &saveptr2);
    }

    token = strtok_r(NULL, "|", &saveptr);
    token = strtok_r(token, " ", &saveptr2);
    i = 0;
    while (token != NULL) {
        if (isdigit(token[0])) {
            secondArray[i++] = atoi(token);
        }
        token = strtok_r(NULL, " ", &saveptr2);
    }

}


int win(int *win_num, int *my_num) {
    
    int win = 0;
    int i = 0;
    int j = 0;
    while(my_num[i] != 0){
        j = 0;
        while(win_num[j] != 0){
            
            if(my_num[i] == win_num[j] && win == 0)
                win = 1;
            else if(my_num[i] == win_num[j] && win != 0)
                win *= 2;


            j++;
        }
        i++;
    }
    return win;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide the file path as a command-line argument.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    Card card;
    int total_win = 0;

    char line[DATA_SIZE];

    while (fgets(line, sizeof(line), file) != NULL) {

        sscanf(line, "Card %d: %[^\n]", &card.number, &card.info);

        extractNumbers(card.info, card.win_num, card.my_num);
        total_win += win(card.win_num, card.my_num);

    }

    printf("Win: %d\n", total_win);

    fclose(file);

    return 0;
}
