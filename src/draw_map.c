/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-romane.cauvez
** File description:
** draw_map
*/

#include "window.h"

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
    sfVertex v2 = {.position = p2, .color = color, .texCoords = {512, 0}};
    sfVertex v3 = {.position = p3, .color = color, .texCoords = {512, 512}};
    sfVertex v4 = {.position = p4, .color = color, .texCoords = {0, 512}};

    if (!quad)
        return NULL;
    sfVertexArray_append(quad, v1);
    sfVertexArray_append(quad, v2);
    sfVertexArray_append(quad, v3);
    sfVertexArray_append(quad, v4);
    sfVertexArray_setPrimitiveType(quad, sfQuads);
    return quad;
}

int draw_lines(sfVector2i id, window_t *win)
{
    sfVertexArray *line = NULL;

    if (id.x < SIZE_MAP - 1)
        line = create_line(&win->map_2d[id.y][id.x],
            &win->map_2d[id.y][id.x + 1]);
    if (id.y < SIZE_MAP - 1)
        line = create_line(&win->map_2d[id.y][id.x],
            &win->map_2d[id.y + 1][id.x]);
    if (line) {
        sfRenderWindow_drawVertexArray(win->win, line, NULL);
        sfVertexArray_destroy(line);
    }
    return 0;
}

int draw_layers(window_t *win, layers_t *la, sfRenderStates *st, sfVector2i id)
{
    if (win->map[id.y][id.x] < -20)
        st->texture = la->text_rock;
    if (win->map[id.y][id.x] >= -20 && win->map[id.y][id.x] < 0)
        st->texture = la->text_dirt;
    if (win->map[id.y][id.x] >= 0 && win->map[id.y][id.x] <= 20)
        st->texture = la->text_grass;
    if (win->map[id.y][id.x] > 20 && win->map[id.y][id.x] < 50)
        st->texture = la->text_rock;
    if (win->map[id.y][id.x] >= 50)
        st->texture = la->text_snow;
    return 0;
}

int draw_quads(sfVector2i id, window_t *win, layers_t *layers)
{
    sfRenderStates state = {
        .blendMode = sfBlendAlpha,
        .transform = sfTransform_Identity,
        .texture = layers->text_grass,
        .shader = NULL
    };
    sfVertexArray *quad = NULL;

    if (id.x < SIZE_MAP - 1 && id.y < SIZE_MAP - 1) {
        quad = create_textured_quad(
            win->map_2d[id.y][id.x], win->map_2d[id.y][id.x + 1],
            win->map_2d[id.y + 1][id.x + 1], win->map_2d[id.y + 1][id.x]);
        if (quad) {
            draw_layers(win, layers, &state, id);
            sfRenderWindow_drawVertexArray(win->win, quad, &state);
            sfVertexArray_destroy(quad);
        }
    }
    return 0;
}

void draw_2d_map(window_t *win, layers_t *layers)
{
    int start_x = 0;
    int end_x = SIZE_MAP;
    int start_y = 0;
    int end_y = SIZE_MAP;
    int step_x = 1;
    int step_y = 1;

    if (win->angle_x > M_PI / 2 && win->angle_x < 3 * M_PI / 2) {
        start_x = SIZE_MAP - 1;
        end_x = -1;
        step_x = -1;
    }
    if (win->angle_y > M_PI) {
        start_y = SIZE_MAP - 1;
        end_y = -1;
        step_y = -1;
    }
    for (int y = start_y; y != end_y; y += step_y)
        for (int x = start_x; x != end_x; x += step_x)
            draw_quads((sfVector2i){x, y}, win, layers);
}
