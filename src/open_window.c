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

sfVector2f project_iso_point(sfVector3f v, double angle_x,
    double angle_y, int center)
{
    sfVector2f point_2d = {0.0, 0.0};
    float new_x = 0.0;
    float new_y = 0.0;

    v.x -= center;
    v.y -= center;
    new_x = cos(angle_x) * v.x - sin(angle_x) * v.y;
    new_y = sin(angle_y) * (v.x + v.y) - v.z;
    new_x += center;
    new_y += center;
    point_2d.x = new_x;
    point_2d.y = new_y;
    return point_2d;
}

static window_t *analyse_events(window_t *win, sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(win->win);
    if (event->type == sfEvtMouseButtonPressed) {
        win->mouse_pressed = 1;
    }
    if (event->type == sfEvtMouseButtonReleased)
        win->mouse_pressed = 0;
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyU) {
            win->up = 1;
            win->down = 0;
        }
        if (event->key.code == sfKeyD) {
            win->down = 1;
            win->up = 0;
        }
        if (event->key.code == sfKeyAdd) {
            scale_map(win->map_2d, SIZE_OF_MAP, SIZE_OF_MAP, 1.01);
            printf("ZOOM\n");
        }
        if (event->key.code == sfKeySubtract) {
            scale_map(win->map_2d, SIZE_OF_MAP, SIZE_OF_MAP, 0.99);
            printf("DEZOOM\n");
        }
        win = handle_rotations(event, win);
    }
    return win;
}

static window_t *create_mount_and_valley(sfVector2i mouse_pos, window_t *win, int y)
{
    for (int x = 0; x < win->size_of_map; x++) {
        if (((win->map_2d[y][x].x - mouse_pos.x) *
            (win->map_2d[y][x].x - mouse_pos.x)) +
            ((win->map_2d[y][x].y - mouse_pos.y) *
            (win->map_2d[y][x].y - mouse_pos.y)) <=
            ((win->tile_size + win->tile_size) *
            (win->tile_size + win->tile_size)) && win->up == 1)
            win->map[y][x] += 2;
        if (((win->map_2d[y][x].x - mouse_pos.x) *
            (win->map_2d[y][x].x - mouse_pos.x)) +
            ((win->map_2d[y][x].y - mouse_pos.y) *
            (win->map_2d[y][x].y - mouse_pos.y)) <=
            ((win->tile_size + win->tile_size) *
            (win->tile_size + win->tile_size)) && win->down == 1)
            win->map[y][x] -= 2;
    }
    win->map_2d = rotate_map(win);
    return win;
}



int while_window_open(window_t *win, sfEvent event)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    while (sfRenderWindow_pollEvent(win->win, &event))
        win = analyse_events(win, &event);
    if (win->mouse_pressed == 1) {
        for (int y = 0; y < win->size_of_map; y++)
            create_mount_and_valley(mouse_pos, win, y);
    }
    return win->mouse_pressed;
}

int open_entry_window(void)
{
    window_t *win = create_struct();
    sfEvent event;
    sfTexture *texture = sfTexture_createFromFile("assets/herbe.jpg", NULL);

    sfRenderWindow_setFramerateLimit(win->win, 60);
    while (sfRenderWindow_isOpen(win->win)) {
        sfRenderWindow_clear(win->win, sfBlue);
        win->mouse_pressed = while_window_open(win, event);

        //scale_map(win->map_2d, SIZE_OF_MAP, SIZE_OF_MAP, 1.01);
        draw_2d_map(win, texture);
        sfRenderWindow_display(win->win);
    }
    my_destroy(win);
    return 0;
}
