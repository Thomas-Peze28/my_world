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
        for (int j = 0; j < size; j++) {
            map[i][j] = rand() % 16 - 8;
            map[i][j] = 0;
        }
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
    win->up = -1;
    win->down = -1;
    return win;
}

void button_set(buttons_t *buttons)
{
    sfSprite_setTexture(buttons->button_add, buttons->text_add_idle,
        sfTrue);
    sfSprite_setTexture(buttons->button_dig, buttons->text_dig_idle,
        sfTrue);
    sfSprite_setScale(buttons->button_add, (sfVector2f){0.5, 0.5});
    sfSprite_setScale(buttons->button_dig, (sfVector2f){0.5, 0.5});
    sfSprite_setPosition(buttons->button_add, (sfVector2f){10, 10});
    sfSprite_setPosition(buttons->button_dig, (sfVector2f){10, 150});
}

buttons_t *create_buttons(void)
{
    buttons_t *b = malloc(sizeof(buttons_t));

    b->text_add_idle = sfTexture_createFromFile("assets/add_idle.png",
        NULL);
    b->text_add_hover = sfTexture_createFromFile("assets/add_hover.png",
        NULL);
    b->text_add_selected = sfTexture_createFromFile("assets/add_selected.png",
        NULL);
    b->text_dig_idle = sfTexture_createFromFile("assets/dig_idle.png",
        NULL);
    b->text_dig_hover = sfTexture_createFromFile("assets/dig_hover.png",
        NULL);
    b->text_dig_selected = sfTexture_createFromFile("assets/dig_selected.png",
        NULL);
    b->button_add = sfSprite_create();
    b->button_dig = sfSprite_create();
    button_set(b);
    return b;
}
