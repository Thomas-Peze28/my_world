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

    if (mouse_pos.x >= bounds.left &&
        mouse_pos.x <= bounds.left + bounds.width &&
        mouse_pos.y >= bounds.top && mouse_pos.y <= bounds.top + bounds.height)
        return 1;
    return 0;
}
