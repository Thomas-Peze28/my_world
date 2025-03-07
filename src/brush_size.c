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

void manage_brush(window_t *win, sfEvent *event)
{
    if (event->key.code == sfKeyA)
        win->brush_size++;
    if (event->key.code == sfKeyZ)
        win->brush_size--;
}
