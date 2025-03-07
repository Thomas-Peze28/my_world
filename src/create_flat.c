/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** open_window
*/

#include <SFML/Graphics.h>
#include "window.h"
#include <math.h>
#include <stdio.h>

window_t *create_flat(sfVector2i mouse_pos, window_t *win, int y)
{
    for (int x = 0; x < win->size_of_map; x++) {
        if (((win->map_2d[y][x].x - mouse_pos.x) *
            (win->map_2d[y][x].x - mouse_pos.x)) +
            ((win->map_2d[y][x].y - mouse_pos.y) *
            (win->map_2d[y][x].y - mouse_pos.y)) <=
            ((win->brush_size * 2) *
            (win->brush_size * 2)) && win->flat == 1)
            win->map[y][x] = 0;
    }
    win->map_2d = rotate_map(win);
    return win;
}
