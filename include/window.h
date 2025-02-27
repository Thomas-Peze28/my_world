/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** hunter.h
*/


#ifndef WINDOW_H
    #define WINDOW_H
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Window/WindowBase.h>
    #include <SFML/Graphics/Color.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <unistd.h>
    #include <stdlib.h>
    #define M_PI 3.14159265358979323846
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080

typedef struct window_s {
    int tile_size;
    int size_of_map;
    sfRenderWindow *win;
    sfVector2f **map_2d;
    int **map;
    int mouse_pressed;
    double angle_x;
    double angle_y;
    int up;
    int down;
} window_t;


void my_destroy(window_t *win);
sfVector2f project_iso_point(sfVector3f v, double angle_x,
    double angle_y, int center);
int draw_2d_map(window_t *win, sfTexture *texture);
window_t *handle_rotations(sfEvent *event, window_t *win);
int open_entry_window(void);
window_t *create_struct(void);

#endif
