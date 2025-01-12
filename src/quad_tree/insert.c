/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** insert
*/
#include "my.h"
#include "include.h"

bool q_tree_size(sfFloatRect zone)
{
    if (zone.height < 20.00){
        return true;
    }
    return false;
}

bool check_in(quad_t_t *quad_t, plane_t *plane)
{
    float l = quad_t->zone.left;
    float t = quad_t->zone.top;
    float w = quad_t->zone.width;
    float h = quad_t->zone.height;
    sfVector2f hb = sfRectangleShape_getPosition(plane->h_b);
    sfVector2f size = sfRectangleShape_getSize(plane->h_b);

    if ((hb.x - size.x >= l || hb.x + size.x >= l) &&
        (hb.x - size.x <= l + w || hb.x + size.x <= l + w) &&
        (hb.y - size.y >= t || hb.y + size.y >= t) &&
        (hb.y - size.y <= t + h || hb.y + size.y <= t + h))
        return true;
    return false;
}

void insert(quad_t_t *q_tree, plane_t *plane, list_t *tower_l)
{
    node_t *current_q = q_tree->quad_l->head;

    if (plane->is_dead == true || !check_in(q_tree, plane) ||
        is_in_tower(plane, tower_l))
        return;
    if ((q_tree->ac_l->size < q_tree->capacity ||
        q_tree_size(q_tree->zone) == true) && q_tree->is_div == false)
        push_back(q_tree->ac_l, plane);
    else if (q_tree->is_div == false && q_tree->ac_l->size >= q_tree->capacity
        && q_tree_size(q_tree->zone) == false)
        sub_divise(q_tree);
    if (q_tree->is_div == true){
        for (; current_q != NULL; current_q = current_q->next)
            insert(((quad_t_t *)current_q->data), plane, tower_l);
    }
}
