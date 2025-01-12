/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** set_quad_tree
*/
#include "include.h"
#include "my.h"

quad_t_t *set_quad_tree(sfFloatRect zone)
{
    quad_t_t *q_tree = malloc(sizeof(quad_t_t));

    if (!q_tree)
        return NULL;
    q_tree->zone = zone;
    q_tree->h_b = sfRectangleShape_create();
    sfRectangleShape_setPosition(q_tree->h_b,
        (sfVector2f){zone.left, zone.top});
    sfRectangleShape_setSize(q_tree->h_b,
        (sfVector2f){zone.width, zone.height});
    sfRectangleShape_setFillColor(q_tree->h_b, sfTransparent);
    sfRectangleShape_setOutlineColor(q_tree->h_b, sfGreen);
    sfRectangleShape_setOutlineThickness(q_tree->h_b, 1);
    q_tree->capacity = 10;
    q_tree->is_div = false;
    q_tree->ac_l = list_create();
    q_tree->quad_l = list_create();
    return q_tree;
}
