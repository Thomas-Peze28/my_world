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

int is_mouse_on_button(sfSprite *sprite, sfVector2i mouse_pos)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);

    if (mouse_pos.x >= bounds.left && mouse_pos.x <= bounds.left + bounds.width &&
        mouse_pos.y >= bounds.top && mouse_pos.y <= bounds.top + bounds.height)
        return 1;
    return 0;
}

window_t *analyse_buttons(window_t *win, sfEvent event, buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    if (is_mouse_on_button(buttons->button_add, mouse_pos) && !win->up)
        sfSprite_setTexture(buttons->button_add, buttons->texture_add_hover, sfTrue);
    if (!is_mouse_on_button(buttons->button_add, mouse_pos) && win->up == 0)
        sfSprite_setTexture(buttons->button_add, buttons->texture_add_idle, sfTrue);
    if (is_mouse_on_button(buttons->button_dig, mouse_pos) && !win->down)
        sfSprite_setTexture(buttons->button_dig, buttons->texture_dig_hover, sfTrue);
    if (!is_mouse_on_button(buttons->button_dig, mouse_pos) && win->down == 0)
        sfSprite_setTexture(buttons->button_dig, buttons->texture_dig_idle, sfTrue);
    if (is_mouse_on_button(buttons->button_add, mouse_pos))
        if (event.type == sfEvtMouseButtonPressed || win->up == 1) {
            win->up = 1;
            win->down = 0;
            sfSprite_setTexture(buttons->button_add, buttons->texture_add_selected, sfTrue);
        }
    if (is_mouse_on_button(buttons->button_dig, mouse_pos))
        if (event.type == sfEvtMouseButtonPressed) {
            win->down = 1;
            win->up = 0;
            sfSprite_setTexture(buttons->button_dig, buttons->texture_dig_selected, sfTrue);
        }
    return win;
}
