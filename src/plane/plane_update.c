/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** plane_update
*/
#include "include.h"

static
void move_ac(plane_t *plane)
{
    float angle = atan2f(plane->pos_e.y - plane->pos.y,
        plane->pos_e.x - plane->pos.x);

    plane->pos.x += cos(angle) * plane->speed / 20.f;
    plane->pos.y += sin(angle) * plane->speed / 20.f;
    sfSprite_setPosition(plane->sprite, plane->pos);
    sfRectangleShape_setPosition(plane->h_b, plane->pos);
}

static
bool verify_is_arrived(plane_t *plane)
{
    if (plane->pos.x - plane->speed / 20.f < plane->pos_e.x &&
        plane->pos.x + plane->speed / 20.f > plane->pos_e.x &&
        plane->pos.y - plane->speed / 20.f < plane->pos_e.y &&
        plane->pos.y + plane->speed / 20.f > plane->pos_e.y)
        return true;
    return false;
}

bool is_in_window(plane_t *plane)
{
    if (plane->pos.x < 0.0 || plane->pos.x > 1980.0 ||
        plane->pos.y < 0.0 || plane->pos.y > 1080.0)
        return false;
    return true;
}

void plane_l_update(list_t *plane_l, radar_t *radar)
{
    node_t *next = NULL;

    radar->q_tree = set_quad_tree((sfFloatRect){0, 0, 1920, 1080});
    for (node_t *cur = plane_l->head; cur != NULL; cur = next){
        next = cur->next;
        if (((plane_t *)cur->data)->is_dead == true ||
            verify_is_arrived((plane_t *)cur->data) == true ||
            is_in_window((plane_t *)cur->data) == false){
            destroy_plane(((plane_t *)cur->data));
            destroy_nodes(plane_l, cur);
            continue;
        }
        move_ac(((plane_t *)cur->data));
        insert(radar->q_tree, (plane_t *)cur->data, radar->list->tower_l);
    }
}
