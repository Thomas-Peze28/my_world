/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-romane.cauvez
** File description:
** create_struct
*/

#include "window.h"

static int **create_map_rand(int size)
{
    int **map = malloc(sizeof(int *) * size);

    for (int i = 0; i < size; i++) {
        map[i] = malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++)
            // map[i][j] = rand() % 16 - 8;
            map[i][j] = 0;
    }
    return map;
}

static sfVector2f **create_2d_map(window_t *win, double angle_x,
    double angle_y)
{
    sfVector2f **map_2d = malloc(win->size_of_map * sizeof(sfVector2f *));
    int offset_x = WINDOW_WIDTH / 2;
    sfVector2f projected = {0.0, 0.0};

    if (!map_2d)
        return NULL;
    for (int y = 0; y < win->size_of_map; y++) {
        map_2d[y] = malloc(win->size_of_map * sizeof(sfVector2f));
        if (!map_2d[y])
            return NULL;
        for (int x = 0; x < win->size_of_map; x++) {
            projected = project_iso_point((sfVector3f){x * win->tile_size,
                y * win->tile_size, win->map[y][x] * 5}, angle_x, angle_y, 0);
            projected.x += offset_x;
            map_2d[y][x] = projected;
        }
    }
    return map_2d;
}

window_t *create_struct(void)
{
    window_t *win = malloc(sizeof(window_t));

    win->angle_x = 4.00;
    win->angle_y = 5.14;
    win->size_of_map = 30;
    win->map = create_map_rand(win->size_of_map);
    win->tile_size = 40;
    win->map_2d = create_2d_map(win, (M_PI / win->angle_x),
        (M_PI / win->angle_y));
    win->mouse_pressed = 0;
    win->win = sfRenderWindow_create((sfVideoMode){WINDOW_WIDTH,
        WINDOW_HEIGHT, 32}, "My_world", sfDefaultStyle, NULL);
    win->up = 1;
    win->down = 0;
    return win;
}
