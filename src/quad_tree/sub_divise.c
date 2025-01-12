/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** sub_divise
*/
#include "include.h"
#include "my.h"

void share_plane(quad_t_t *q_tree)
{
    node_t *current = q_tree->ac_l->head;
    node_t *next = NULL;

    while (current != NULL){
        next = current->next;
        insert(q_tree, ((plane_t *)current->data), NULL);
        destroy_nodes(q_tree->ac_l, current);
        current = next;
    }
}

void sub_divise(quad_t_t *q_tree)
{
    float l = q_tree->zone.left;
    float t = q_tree->zone.top;
    float w = q_tree->zone.width;
    float h = q_tree->zone.height;
    sfFloatRect nw = (sfFloatRect){l, t, w / 2, h / 2};
    sfFloatRect ne = (sfFloatRect){l + w / 2, t, w / 2, h / 2};
    sfFloatRect sw = (sfFloatRect){l, t + h / 2, w / 2, h / 2};
    sfFloatRect se = (sfFloatRect){l + w / 2, t + h / 2, w / 2, h / 2};

    push_back(q_tree->quad_l, set_quad_tree(ne));
    push_back(q_tree->quad_l, set_quad_tree(nw));
    push_back(q_tree->quad_l, set_quad_tree(se));
    push_back(q_tree->quad_l, set_quad_tree(sw));
    q_tree->is_div = true;
    share_plane(q_tree);
}
