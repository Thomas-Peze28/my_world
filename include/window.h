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
#define M_PI	3.14159265358979323846
#define ANGLE_X  (M_PI / 4)  // 45 degrees in radians
#define ANGLE_Y  (M_PI / 5.14) // 35 degrees in radians
#define TILE_SIZE 64  // Sampling size for the map
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define SIZE_OF_MAP 15

// typedef struct button_s {
//     sfRectangleShape *square;
// } button_t;

// button_t *init_button(sfVector2f position, sfVector2f size, sfColor color);
// button_t **init_buttons(int nbr_square, sfRenderWindow *win);
// sfBool is_clicked(button_t *button, sfMouseButtonEvent *event);
// sfBool is_hover(button_t *button, sfMouseMoveEvent *event);
// int open_window(void);
void my_destroy(sfRenderWindow *win, sfVector2f **map_2d);
int open_entry_window(void);
#endif
