/*
Name: Isha Gadani
Student Number: 041085940
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define MAP_MAX_WIDTH 32
#define MAP_MAX_HEIGHT 32
#define TREASURE_MAX ((MAP_MAX_WIDTH * MAP_MAX_HEIGHT) / 4)
#define CODE_LENGTH 4

typedef struct {
    int width;
    int height;
    char **map;
    int num_treasures;
    char **treasure_codes;
    int **treasure_locations;
    int treasures_found;
} Game;

void initialize_game(Game *game);
void generate_treasure_locations(Game *game);
void print_map(Game *game, int cheat_mode);
void dig(Game *game, int x, int y, int *cheat_mode);
void free_game(Game *game);

int main() {
    Game game;
    int choice;
    int x, y;
    int cheat_mode = 0;

    initialize_game(&game);

    while (1) {
        printf("1 - Dig at a spot  | 2 - Exit Game      | 3 - Cheat!\n");
        if (cheat_mode)
            printf("CHEAT -> ");
        printf("-> ");
        if (scanf("%d", &choice) != 1) {
            if (feof(stdin)) {
                printf("\nEnd of File (EOF) input. Exiting.\n");
                free_game(&game);
                return 3;
            }
            continue; /*Discard non-numeric input*/
        }

        switch (choice) {
            case 1:
                print_map(&game, cheat_mode);
                printf("Where would you like to dig?\n");
                printf("x = ");
                scanf("%d", &x);
                printf("y = ");
                scanf("%d", &y);
                dig(&game, x, y, &cheat_mode);
                break;
            case 2:
                printf("Exiting game.\n");
                free_game(&game);
                return 0;
            case 3:
                if (cheat_mode) {
                    printf("Cheat mode already enabled!\n");
                } else {
                    cheat_mode = 1;
                    printf("Cheat mode enabled!\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

void initialize_game(Game *game) {
    int i;
    int j;
    srand(time(0));


    printf("Enter map width: ");
    scanf("%d", &(game->width));
    printf("Enter map height: ");
    scanf("%d", &(game->height));

    if (game->width < 2 || game->width > MAP_MAX_WIDTH || game->height < 2 || game->height > MAP_MAX_HEIGHT) {
        printf("Map dimensions out of range.\n");
        exit(1);
    }

    game->map = (char **)malloc(game->height * sizeof(char *));
    if (game->map == NULL) {
        printf("Memory allocation failed.\n");
        exit(4);
    }
    for (i = 0; i < game->height; i++) {
        game->map[i] = (char *)malloc((game->width + 1) * sizeof(char)); /*+1 for null terminator*/
        if (game->map[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(4);
        }
        for (j = 0; j < game->width; j++) {
            game->map[i][j] = ' ';
        }
        game->map[i][game->width] = '\0'; /*Null terminate the string*/
    }

    printf("Enter number of treasures to add: ");
    scanf("%d", &(game->num_treasures));

    if (game->num_treasures < 1 || game->num_treasures > TREASURE_MAX) {
        printf("Invalid number of treasures.\n");
        exit(1);
    }

    game->treasure_codes = (char **)malloc(game->num_treasures * sizeof(char *));
    game->treasure_locations = (int **)malloc(game->num_treasures * sizeof(int *));
    if (game->treasure_codes == NULL || game->treasure_locations == NULL) {
        printf("Memory allocation failed.\n");
        exit(4);
    }
    for (i = 0; i < game->num_treasures; i++) {
        game->treasure_codes[i] = (char *)malloc((CODE_LENGTH + 1) * sizeof(char)); /*+1 for null terminator*/
        if (game->treasure_codes[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(4);
        }
        printf("Enter treasure #%d code (e.g. T001): ", i + 1);
        scanf("%s", game->treasure_codes[i]);
        if (strlen(game->treasure_codes[i]) != CODE_LENGTH || game->treasure_codes[i][0] != 'T' ||
            !isdigit(game->treasure_codes[i][1]) || !isdigit(game->treasure_codes[i][2]) ||
            !isdigit(game->treasure_codes[i][3])) {
            printf("Treasure codes must be a 'T' followed by 3 digits\n");
            i--; /*Repeat the same iteration*/
            continue;
        }
        for (j = 0; j < i; j++) {
            if (strcmp(game->treasure_codes[i], game->treasure_codes[j]) == 0) {
                printf("Treasure code already in use.\n");
                i--; /*epeat the same iteration*/
                break;
            }
        }
        game->treasure_locations[i] = (int *)malloc(2 * sizeof(int));
        if (game->treasure_locations[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(4);
        }
    }

    game->treasures_found = 0;

    generate_treasure_locations(game);
}

void generate_treasure_locations(Game *game) {
    
    int num_generated;
    int max_possible_treasures;
    int x;
    int y;
    num_generated = 0;
    max_possible_treasures = (game->width * game->height) / 4;

    if (game->num_treasures > max_possible_treasures) {
        printf("Invalid number of treasures.\n");
        exit(1);
    }

    
    while (num_generated < game->num_treasures) {
        x = rand() % game->width;
        y = rand() % game->height;

        /*Check if already occupied*/
        if (game->map[y][x] != ' ') {
            continue;
        }

        game->treasure_locations[num_generated][0] = x;
        game->treasure_locations[num_generated][1] = y;
        game->map[y][x] = '!'; /*Place a treasure marker on the map*/
        num_generated++;
    }
}

void print_map(Game *game, int cheat_mode) {
    int i;
    int j;

    printf("Map:\n\n");
    printf("   ");
    for (i = 0; i < game->width; i++) {
        printf("%d", i / 10);
    }
    printf("\n");
    printf("   ");
    for (i = 0; i < game->width; i++) {
        printf("%d", i % 10);
    }
    printf("\n");
    printf("  ");
    for (i = 0; i < game->width; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < game->height; i++) {
        printf("%02d|", i);
        for (j = 0; j < game->width; j++) {
            char display_char = (cheat_mode && game->map[i][j] == ' ' && game->map[i][j] != 'x') ? '!' : game->map[i][j];
            printf("%c", display_char);
        }
        printf("\n");
    }
}

void dig(Game *game, int x, int y, int *cheat_mode) {
    int i; 

    if (x < 0 || x >= game->width || y < 0 || y >= game->height) {
        printf("Invalid coordinates.\n");
        return;
    }

    if (game->map[y][x] != ' ') {
        printf("You already dug there.\n");
        return;
    }

    for (i = 0; i < game->num_treasures; i++) {
        if (game->treasure_locations[i][0] == x && game->treasure_locations[i][1] == y) {
            printf("Congratulations, you found a treasure! (code: %s)\n", game->treasure_codes[i]);
            game->treasures_found++;
            game->map[y][x] = '$';
            if (game->treasures_found == game->num_treasures) {
                printf("Congratulations, you found all the treasures!\n");
                free_game(game);
                exit(EXIT_SUCCESS);
            }
            return;
        }
    }

    printf("You found nothing there.\n");
    game->map[y][x] = 'x';
}

void free_game(Game *game) {
    int i; 

    for (i = 0; i < game->height; i++) {
        free(game->map[i]);
    }
    free(game->map);

    for (i = 0; i < game->num_treasures; i++) {
        free(game->treasure_codes[i]);
        free(game->treasure_locations[i]);
    }
    free(game->treasure_codes);
    free(game->treasure_locations);
}
