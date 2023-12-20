#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DATA_SIZE 142

typedef struct
{
    int *ptr;
    size_t used;
    size_t size;
} IntArray;

typedef struct
{
    int number;
    char info[200];
    IntArray win_num;
    IntArray my_num;
    int win;
    int amount;
} Card;

typedef struct
{
    Card *ptr;
    size_t used;
    size_t size;
} CardArray;

void extractNumbers(Card *card)
{

    char *saveptr, *saveptr2;
    char *token = strtok_r(card->info, "|", &saveptr);

    token = strtok_r(token, " ", &saveptr2);
    int i = 0;
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            card->win_num.ptr = (int *)realloc(card->win_num.ptr, (i + 1) * sizeof(int));
            card->win_num.size = i + 1;
            card->win_num.ptr[i++] = atoi(token);
        }
        token = strtok_r(NULL, " ", &saveptr2);
    }

    token = strtok_r(NULL, "|", &saveptr);
    token = strtok_r(token, " ", &saveptr2);
    i = 0;
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            card->my_num.ptr = (int *)realloc(card->my_num.ptr, (i + 1) * sizeof(int));
            card->my_num.size = i + 1;
            card->my_num.ptr[i++] = atoi(token);
        }
        token = strtok_r(NULL, " ", &saveptr2);
    }
}

int win(Card *card)
{
    card->win = 0;
    for (int i = 0; i < card->my_num.size; i++)
    {
        for (int j = 0; j < card->win_num.size; j++)
        {
            if (card->my_num.ptr[i] == card->win_num.ptr[j])
                card->win++;
        }
    }
    return card->win;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide the file path as a command-line argument.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    Card card = {
        .number = 0,
        .info = "",
        .win_num = {
            .ptr = NULL,
            .size = 0},
        .my_num = {.ptr = NULL, .size = 0},
        .win = 0};

    CardArray cards = {
        .ptr = NULL,
        .used = 0,
        .size = 0};

    int total_win = 0;

    char line[DATA_SIZE];
    memset(line, 0, sizeof(line));

    while (fgets(line, sizeof(line), file) != NULL)
    {

        cards.ptr = (Card *)realloc(cards.ptr, (++cards.size) * sizeof(Card));
        sscanf(line, "Card %d: %[^\n]", &card.number, &card.info);

        extractNumbers(&card);
        win(&card);
        card.amount = 1;

        cards.ptr[cards.size - 1] = card;
    }

    for (int arr = 0; arr < cards.size; arr++)
    {
        for (int j = 1; j <= cards.ptr[arr].win; j++)
        {
            cards.ptr[arr + j].amount += cards.ptr[arr].amount;
        }
    }

    for (int i = 0; i < cards.size; i++)
    {
        total_win += cards.ptr[i].amount;
    }
    printf("Total win %d\n", total_win);

    fclose(file);

    return 0;
}
