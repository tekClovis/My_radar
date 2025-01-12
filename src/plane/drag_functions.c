/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** drag_functions
*/
#include "include.h"

void drop_plane(radar_t *radar)
{
    push_back(radar->list->plane_l, radar->drag_plane);
    radar->drag_plane = NULL;
}

void grab_plane(float mouse_x, float mouse_y, radar_t *radar)
{
    sfVector2f h_b = (sfVector2f){0, 0};
    sfVector2f pos = (sfVector2f){0, 0};
    sfVector2f og = (sfVector2f){0, 0};

    for (node_t *cur = radar->list->plane_l->head; cur; cur = cur->next){
        h_b = sfRectangleShape_getSize(((plane_t *)cur->data)->h_b);
        pos = sfRectangleShape_getPosition(((plane_t *)cur->data)->h_b);
        og = sfRectangleShape_getOrigin(((plane_t *)cur->data)->h_b);
        if (mouse_x > pos.x - og.x * 2 && mouse_y > pos.y - og.y * 2 &&
            mouse_x < pos.x - og.x * 2 + h_b.x * 2 && mouse_y <
            pos.y + h_b.y * 2 - og.y * 2 && radar->drag_plane == NULL){
            radar->drag_plane = (plane_t *)cur->data;
            destroy_nodes(radar->list->plane_l, cur);
            return;
        }
    }
}

void move_drag(int mouse_x, int mouse_y, plane_t *drag_plane)
{
    float angle = 0.0;

    if (drag_plane == NULL)
        return;
    angle = atan2f(drag_plane->pos.y - drag_plane->pos_e.y,
    drag_plane->pos.x - drag_plane->pos_e.x);
    drag_plane->pos.x = mouse_x;
    drag_plane->pos.y = mouse_y;
    sfSprite_setPosition(drag_plane->sprite, drag_plane->pos);
    sfRectangleShape_setPosition(drag_plane->h_b, drag_plane->pos);
    sfSprite_setRotation(drag_plane->sprite, angle * (180.f / 3.14));
}
