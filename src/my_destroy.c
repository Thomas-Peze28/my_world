/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** my_destroy.c
*/

#include <SFML/Graphics.h>
#include "window.h"

void my_destroy(sfRenderWindow *win, sfVector2f **map_2d, int **map)
{
    for (int i = 0; i < SIZE_OF_MAP; i++) {
        free(map[i]);
        free(map_2d[i]);
    }
    free(map);
    free(map_2d);
    sfRenderWindow_destroy(win);
}
