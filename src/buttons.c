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

void apply_button_text(window_t *win, buttons_t *but)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    if ((is_mouse_on_button(but->button_add, mouse_pos) && !win->up))
        sfSprite_setTexture(but->button_add, but->text_add_hover, sfTrue);
    if (!is_mouse_on_button(but->button_add, mouse_pos) && win->up == 0)
        sfSprite_setTexture(but->button_add, but->text_add_idle, sfTrue);
    if ((is_mouse_on_button(but->button_dig, mouse_pos) && !win->down))
        sfSprite_setTexture(but->button_dig, but->text_dig_hover, sfTrue);
    if (!is_mouse_on_button(but->button_dig, mouse_pos) && win->down == 0)
        sfSprite_setTexture(but->button_dig, but->text_dig_idle, sfTrue);
    if ((is_mouse_on_button(but->button_flat, mouse_pos) && !win->flat))
        sfSprite_setTexture(but->button_flat, but->text_flat_hover, sfTrue);
    if (!is_mouse_on_button(but->button_flat, mouse_pos) && win->flat == 0)
        sfSprite_setTexture(but->button_flat, but->text_flat_idle, sfTrue);
}

void update_add_button(sfVector2i mouse_pos, window_t *win, sfEvent event,
    buttons_t *but)
{
    if (is_mouse_on_button(but->button_add, mouse_pos))
        if (event.type == sfEvtMouseButtonPressed) {
            win->up = 1;
            win->down = 0;
            win->flat = 0;
            sfSprite_setTexture(but->button_add, but->text_add_selected,
                sfTrue);
        }
}

void update_dig_button(sfVector2i mouse_pos, window_t *win, sfEvent event,
    buttons_t *but)
{
    if (is_mouse_on_button(but->button_dig, mouse_pos))
        if (event.type == sfEvtMouseButtonPressed) {
            win->down = 1;
            win->up = 0;
            win->flat = 0;
            sfSprite_setTexture(but->button_dig, but->text_dig_selected,
                sfTrue);
        }
}

void update_flat_button(sfVector2i mouse_pos, window_t *win, sfEvent event,
    buttons_t *but)
{
    if (is_mouse_on_button(but->button_flat, mouse_pos))
        if (event.type == sfEvtMouseButtonPressed) {
            win->down = 0;
            win->up = 0;
            win->flat = 1;
            sfSprite_setTexture(but->button_flat, but->text_flat_selected,
                sfTrue);
        }
}

window_t *analyse_buttons(window_t *win, sfEvent event, buttons_t *but)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    apply_button_text(win, but);
    update_add_button(mouse_pos, win, event, but);
    update_dig_button(mouse_pos, win, event, but);
    update_flat_button(mouse_pos, win, event, but);
    return win;
}
