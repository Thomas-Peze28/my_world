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

// camera : when key pressed : '<' ANGLE_X --, '^' ANGLE_Y --, '>' ANGLE_X ++, '⬇️' ANGLE_Y ++

static sfVector2f project_iso_point(int x, int y, int z)
{
    sfVector2f point_2d = {0.0, 0.0};

    point_2d.x = cos(ANGLE_X) * x - cos(ANGLE_X) * y;
    point_2d.y = sin(ANGLE_Y) * y + sin(ANGLE_Y) * x - z;
    return point_2d;
}

static sfVector2f **create_2d_map(int **map, int width, int height)
{
    sfVector2f **map_2d = malloc(height * sizeof(sfVector2f *));
    int offset_x = WINDOW_WIDTH / 2;
    sfVector2f projected = {0.0, 0.0};

    if (!map_2d)
        return NULL;
    for (int y = 0; y < height; y++) {
        map_2d[y] = malloc(width * sizeof(sfVector2f));
        if (!map_2d[y])
            return NULL;
        for (int x = 0; x < width; x++) {
            projected = project_iso_point(x * TILE_SIZE, y * TILE_SIZE,
                map[y][x] * 5);
            projected.x += offset_x;
            map_2d[y][x] = projected;
        }
    }
    return map_2d;
}

static sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};

    if (!vertex_array)
        return NULL;
    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
    return vertex_array;
}

sfVertexArray *create_textured_quad(sfVector2f p1, sfVector2f p2,
    sfVector2f p3, sfVector2f p4)
{
    sfColor color = sfWhite;
    sfVertexArray *quad = sfVertexArray_create();
    sfVertex v1 = {.position = p1, .color = color, .texCoords = {0, 0}};
    sfVertex v2 = {.position = p2, .color = color, .texCoords = {5184, 0}};
    sfVertex v3 = {.position = p3, .color = color, .texCoords = {5184, 3456}};
    sfVertex v4 = {.position = p4, .color = color, .texCoords = {0, 3456}};

    if (!quad)
        return NULL;
    sfVertexArray_append(quad, v1);
    sfVertexArray_append(quad, v2);
    sfVertexArray_append(quad, v3);
    sfVertexArray_append(quad, v4);
    sfVertexArray_setPrimitiveType(quad, sfQuads);
    return quad;
}

int draw_lines(sfVector2i id, sfRenderWindow *window, sfVector2f **map_2d)
{
    sfVertexArray *line = NULL;

    if (id.x < SIZE_OF_MAP - 1)
        line = create_line(&map_2d[id.y][id.x], &map_2d[id.y][id.x + 1]);
    if (id.y < SIZE_OF_MAP - 1)
        line = create_line(&map_2d[id.y][id.x], &map_2d[id.y + 1][id.x]);
    if (line) {
        sfRenderWindow_drawVertexArray(window, line, NULL);
        sfVertexArray_destroy(line);
    }
    return 0;
}

int draw_quads(sfVector2i id, sfRenderWindow *window, sfVector2f **map_2d,
    sfTexture *texture)
{
    sfRenderStates states = {
        .blendMode = sfBlendAlpha,
        .transform = sfTransform_Identity,
        .texture = texture,
        .shader = NULL
    };
    sfVertexArray *quad = NULL;

    if (id.x < SIZE_OF_MAP - 1 && id.y < SIZE_OF_MAP - 1) {
        quad = create_textured_quad(
            map_2d[id.y][id.x], map_2d[id.y][id.x + 1],
            map_2d[id.y + 1][id.x + 1], map_2d[id.y + 1][id.x]);
        if (quad) {
            sfRenderWindow_drawVertexArray(window, quad, &states);
            sfVertexArray_destroy(quad);
        }
    }
    return 0;
}

int draw_2d_map(sfRenderWindow *window, sfVector2f **map_2d,
    sfTexture *texture)
{
    if (!window || !map_2d || !texture)
        return -1;
    for (int y = 0; y < SIZE_OF_MAP; y++) {
        for (int x = 0; x < SIZE_OF_MAP; x++) {
            draw_lines((sfVector2i){x, y}, window, map_2d);
            draw_quads((sfVector2i){x, y}, window, map_2d, texture);
        }
    }
    return 0;
}

static int analyse_events(sfRenderWindow *win, sfEvent *event,
    int mouse_pressed)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(win);
    if (event->type == sfEvtMouseButtonPressed)
        mouse_pressed = 1;
    if (event->type == sfEvtMouseButtonReleased)
        mouse_pressed = 0;
    return mouse_pressed;
}

int while_window_open(sfRenderWindow *win, sfEvent event,
    sfVector2f **my_2d_map, sfTexture *texture, int mouse_pressed)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win);

    while (sfRenderWindow_pollEvent(win, &event))
        mouse_pressed = analyse_events(win, &event, mouse_pressed);
    if (mouse_pressed == 1) {
        for (int y = 0; y < SIZE_OF_MAP; y++) {
            for (int x = 0; x < SIZE_OF_MAP; x++) { 
                if (((my_2d_map[y][x].x - mouse_pos.x) * (my_2d_map[y][x].x - mouse_pos.x)) +
                    ((my_2d_map[y][x].y - mouse_pos.y) * (my_2d_map[y][x].y - mouse_pos.y)) <=
                    ((TILE_SIZE + TILE_SIZE) * (TILE_SIZE + TILE_SIZE)))
                    my_2d_map[y][x].y -= 2;
            }
        }
    }
    draw_2d_map(win, my_2d_map, texture);
    sfRenderWindow_display(win);
    return mouse_pressed;
}

static int **create_map_rand(void)
{
    int **map = malloc(sizeof(int *) * SIZE_OF_MAP);

    for (int i = 0; i < SIZE_OF_MAP; i++) {
        map[i] = malloc(sizeof(int) * SIZE_OF_MAP);
        for (int j = 0; j < SIZE_OF_MAP; j++)
            map[i][j] = rand() % 16 - 8;
    }
    return map;
}

int open_entry_window(void)
{
    sfRenderWindow *win = sfRenderWindow_create((sfVideoMode){WINDOW_WIDTH,
        WINDOW_HEIGHT, 32}, "My_worldbootstrap", sfDefaultStyle, NULL);
    sfEvent event;
    int **map = create_map_rand();
    sfVector2f **my_2d_map = create_2d_map(map, SIZE_OF_MAP, SIZE_OF_MAP);
    sfTexture *texture = sfTexture_createFromFile("assets/herbe.jpg", NULL);
    int mouse_pressed = 0;

    sfRenderWindow_setFramerateLimit(win, 60);
    while (sfRenderWindow_isOpen(win)) {
        sfRenderWindow_clear(win, sfBlack);
        mouse_pressed = while_window_open(win, event, my_2d_map, texture, mouse_pressed);
    }
    my_destroy(win, my_2d_map);
    return 0;
}
