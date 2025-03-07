/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** open_window
*/

#include "window.h"

sfVector2f scale_iso_point(sfVector2f point, sfVector2f center, float scale)
{
    sfVector2f scaled = {0.0, 0.0};

    center.x = 1920.0 / 2;
    center.y = 1080.0 / 2;
    point.x -= center.x;
    point.y -= center.y;
    scaled.x = point.x * scale;
    scaled.y = point.y * scale;
    scaled.x += center.x;
    scaled.y += center.y;
    return scaled;
}

sfVector2f **scale_map(sfVector2f **map_2d, int width, int height,
    float scale_factor)
{
    sfVector2f projected = {0.0, 0.0};
    sfVector2f center = {(float)(width * 40) / 2.0,
        (float)(height * 40) / 2.0};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            projected = scale_iso_point(map_2d[y][x], center, scale_factor);
            map_2d[y][x] = projected;
        }
    }
    return map_2d;
}
