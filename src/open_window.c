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
    v.z += v.y * 0.001 + v.x * 0.001;
    new_x = cos(angle_x) * v.x - sin(angle_x) * v.y;
    new_y = sin(angle_y) * (v.x + v.y) - v.z;
    new_x += center;
    new_y += center;
    point_2d.x = new_x;
    point_2d.y = new_y;
    return point_2d;
}

window_t *analyse_events(window_t *win, sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(win->win);
    if (event->type == sfEvtMouseButtonPressed)
        win->mouse_pressed = 1;
    if (event->type == sfEvtMouseButtonReleased)
        win->mouse_pressed = 0;
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyAdd) {
            win->scale += 0.05;
            win->map_2d = rotate_map(win);
        }
        if (event->key.code == sfKeySubtract) {
            win->scale -= 0.05;
            win->map_2d = rotate_map(win);
        }
        manage_brush(win, event);
        win = handle_rotations(event, win);
    }
    return win;
}

int while_window_open(window_t *win, buttons_t *buttons, sfEvent event)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    while (sfRenderWindow_pollEvent(win->win, &event)) {
        win = analyse_events(win, &event);
        win = analyse_buttons(win, event, buttons);
    }
    if (win->mouse_pressed == 1) {
        for (int y = 0; y < win->size_of_map; y++) {
            create_mount_and_valley(mouse_pos, win, y);
            create_flat(mouse_pos, win, y);
        }
    }
    return win->mouse_pressed;
}

int open_entry_window(void)
{
    window_t *win = create_struct();
    buttons_t *buttons = create_buttons();
    layers_t *layers = create_layers();
    sfEvent event;

    sfRenderWindow_setFramerateLimit(win->win, 60);
    rotate_map(win);
    while (sfRenderWindow_isOpen(win->win)) {
        sfRenderWindow_clear(win->win, sfBlue);
        sfRenderWindow_drawSprite(win->win, layers->sky, NULL);
        win->mouse_pressed = while_window_open(win, buttons, event);
        draw_2d_map(win, layers);
        sfRenderWindow_drawSprite(win->win, buttons->button_add, NULL);
        sfRenderWindow_drawSprite(win->win, buttons->button_dig, NULL);
        sfRenderWindow_drawSprite(win->win, buttons->button_flat, NULL);
        sfRenderWindow_display(win->win);
    }
    my_destroy(win);
    return 0;
}
