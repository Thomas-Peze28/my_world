/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** my_destroy.c
*/

#include <SFML/Graphics.h>
#include "window.h"

void my_destroy(window_t *win)
{
    for (int i = 0; i < win->size_of_map; i++) {
        free(win->map[i]);
        free(win->map_2d[i]);
    }
    free(win->map);
    free(win->map_2d);
    sfRenderWindow_destroy(win->win);
}
