/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** is_in_tower
*/
#include "include.h"
#include "my.h"

bool is_in_tower(plane_t *plane, list_t *tower_l)
{
    node_t *current_tower = NULL;
    sfVector2f pos_t = {0, 0};
    float rad = 0.0;

    sfRectangleShape_setOutlineColor(plane->h_b, sfRed);
    if (tower_l == NULL)
        return false;
    current_tower = tower_l->head;
    rad = sfCircleShape_getRadius(((tower_t *)current_tower->data)->h_b);
    for (; current_tower != NULL; current_tower = current_tower->next){
        pos_t = sfCircleShape_getPosition(
            ((tower_t *)current_tower->data)->h_b);
        rad = sfCircleShape_getRadius(((tower_t *)current_tower->data)->h_b);
        if (powf(plane->pos.x - pos_t.x, 2) + powf(plane->pos.y - pos_t.y, 2)
            <= powf(rad, 2)){
            sfRectangleShape_setOutlineColor(plane->h_b, sfCyan);
            return true;
        }
    }
    return false;
}
