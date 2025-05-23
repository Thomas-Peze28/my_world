/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-romane.cauvez
** File description:
** rotations
*/

#include "window.h"
#include <stdio.h>

sfVector2f **rotate_map(window_t *win)
{
    sfVector2f projected = {0.0, 0.0};
    sfVector3f point_3d = {0.0, 0.0, 0.0};
    int center = (win->size_of_map * win->tile_size) / 2;

    for (int y = 0; y < win->size_of_map; y++) {
        for (int x = 0; x < win->size_of_map; x++) {
            point_3d = (sfVector3f){
                x * win->tile_size,
                y * win->tile_size,
                win->map[y][x] * 5
            };
            projected = project_iso_point(point_3d, win->angle_x,
                win->angle_y, center);
            projected.x += win->offset_x;
            projected.y += win->offset_y;
            win->map_2d[y][x] = projected;
        }
    }
    scale_map(win->map_2d, win->size_of_map, win->size_of_map, win->scale);
    return win->map_2d;
}

window_t *handle_rotations(sfEvent *event, window_t *win)
{
    if (event->key.code == sfKeyUp) {
        win->angle_y -= 0.01;
        win->map_2d = rotate_map(win);
    }
    if (event->key.code == sfKeyDown) {
        win->angle_y += 0.01;
        win->map_2d = rotate_map(win);
    }
    if (event->key.code == sfKeyLeft) {
        win->angle_x -= 0.01;
        win->map_2d = rotate_map(win);
    }
    if (event->key.code == sfKeyRight) {
        win->angle_x += 0.01;
        win->map_2d = rotate_map(win);
    }
    return win;
}
