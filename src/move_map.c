/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-romane.cauvez
** File description:
** rotations
*/

#include "window.h"
#include <stdio.h>

void manage_moving(window_t *win, sfEvent *event)
{
    if (event->key.code == sfKeyQ) {
        win->offset_x -= 10;
        win->map_2d = rotate_map(win);
    }
    if (event->key.code == sfKeyD) {
        win->offset_x += 10;
        win->map_2d = rotate_map(win);
    }
    if (event->key.code == sfKeyZ) {
        win->offset_y -= 10;
        win->map_2d = rotate_map(win);
    }
    if (event->key.code == sfKeyS) {
        win->offset_y += 10;
        win->map_2d = rotate_map(win);
    }
}
