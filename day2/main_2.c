#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define RED 12
#define GREEN 13
#define BLUE 14

typedef struct
{
    int min_red;
    int min_green;
    int min_blue;
    bool valid;
} GameSpecs;

GameSpecs is_valid(int red, int green, int blue, char *game)
{
    int r = 0, g = 0, b = 0;
    char *saveptr, *saveptr2;

    GameSpecs game_specs = {
        .min_red = 0,
        .min_green = 0,
        .min_blue = 0,
        .valid = true
    };

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

            if (strcmp(color, "red") == 0){
                r += count;
                if (r > game_specs.min_red)
                    game_specs.min_red = r;
            }
            else if (strcmp(color, "green") == 0){
                g += count;
                if (g > game_specs.min_green)
                    game_specs.min_green = g;
            }
            else if (strcmp(color, "blue") == 0){
                b += count;
                if (b > game_specs.min_blue)
                    game_specs.min_blue = b;
            }

            token = strtok_r(NULL, ",", &saveptr2);

            if (game_specs.min_red > red || game_specs.min_green > green || game_specs.min_blue > blue)
                game_specs.valid = false;
            else
                game_specs.valid = true;

        }

        draws = strtok_r(NULL, ";", &saveptr);
    }

    return game_specs;
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
    int sum_of_powers = 0;

    // Read the file line by line until EOF
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char game_info[200];
        int game_number;
        sscanf(line, "Game %d: %[^\n]", &game_number, game_info);
        //printf("Game %d\n", game_number);
        //printf("%s\n", game_info);

        GameSpecs game_specs = is_valid(RED, GREEN, BLUE, game_info);

        if (game_specs.valid)
            sum_possible_games += game_number;

        sum_of_powers += (game_specs.min_red * game_specs.min_green * game_specs.min_blue);
        

        
    }

    printf("Sum of possible games: %d\n", sum_possible_games);
    printf("Sum of powers: %d\n", sum_of_powers);

    // Close the file
    fclose(file);

    return 0;
}