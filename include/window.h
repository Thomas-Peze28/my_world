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
    #include <math.h>
    #define M_PI 3.14159265358979323846
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define SIZE_MAP 30

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
    int flat;
} window_t;

typedef struct buttons_s {
    sfTexture *text_dig_idle;
    sfTexture *text_dig_hover;
    sfTexture *text_dig_selected;
    sfTexture *text_add_idle;
    sfTexture *text_add_hover;
    sfTexture *text_add_selected;
    sfTexture *text_flat_idle;
    sfTexture *text_flat_hover;
    sfTexture *text_flat_selected;
    sfSprite *button_add;
    sfSprite *button_dig;
    sfSprite *button_flat;
} buttons_t;

typedef struct layers_s {
    sfTexture *text_grass;
    sfTexture *text_dirt;
    sfTexture *text_rock;
    sfTexture *text_snow;
    sfTexture *text_sky;
    sfSprite *sky;
} layers_t;

void my_destroy(window_t *win);
sfVector2f project_iso_point(sfVector3f v, double angle_x,
    double angle_y, int center);
void draw_2d_map(window_t *win, layers_t *layers);
window_t *handle_rotations(sfEvent *event, window_t *win);
int open_entry_window(void);
window_t *create_struct(void);
sfVector2f **scale_map(sfVector2f **map_2d, int width, int height,
    float scale);
sfVector2f **rotate_map(window_t *win);
buttons_t *create_buttons(void);
int is_mouse_on_button(sfSprite *sprite, sfVector2i mouse_pos);
window_t *analyse_buttons(window_t *win, sfEvent event, buttons_t *buttons);
layers_t *create_layers(void);
window_t *create_mount_and_valley(sfVector2i mouse_pos, window_t *win, int y);
window_t *create_flat(sfVector2i mouse_pos, window_t *win, int y);
int is_mouse_on_button(sfSprite *sprite, sfVector2i mouse_pos);

#endif
