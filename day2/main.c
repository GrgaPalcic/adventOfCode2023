#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define RED 12
#define GREEN 13
#define BLUE 14


bool is_valid(int red, int green, int blue, char *game)
{
    int r = 0, g = 0, b = 0;
    char *saveptr, *saveptr2;
    bool valid = true;

    char *draws = strtok_r(game, ";", &saveptr);
    while (draws != NULL)
    {
        r = 0, g = 0, b = 0;
        char *token = strtok_r(draws, ",", &saveptr2);
        while (token != NULL)
        {
            int count;
            char color[10];
            sscanf(token, "%d %s", &count, color);

            if (strcmp(color, "red") == 0)
                r += count;
            else if (strcmp(color, "green") == 0)
                g += count;
            else if (strcmp(color, "blue") == 0)
                b += count;

            token = strtok_r(NULL, ",", &saveptr2);

            if (r > red || g > green || b > blue)
                valid = false;

        }

        draws = strtok_r(NULL, ";", &saveptr);
    }

    return valid;
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

    char line[200];
    int sum_possible_games = 0;

    // Read the file line by line until EOF
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char game_info[200];
        int game_number;
        sscanf(line, "Game %d: %[^\n]", &game_number, game_info);
        //printf("Game %d\n", game_number);
        //printf("%s\n", game_info);

        if (is_valid(RED, GREEN, BLUE, game_info))
            sum_possible_games += game_number;
    }

    printf("Sum of possible games: %d\n", sum_possible_games);

    // Close the file
    fclose(file);

    return 0;
}