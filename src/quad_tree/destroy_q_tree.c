/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** destroy_q_tree
*/
#include "include.h"

void destroy_q_tree(quad_t_t *q_tree)
{
    node_t *cur = NULL;
    node_t *next = NULL;

    if (q_tree == NULL)
        return;
    cur = q_tree->ac_l->head;
    for (; cur != NULL; cur = next){
        next = cur->next;
        destroy_nodes(q_tree->ac_l, cur);
    }
    free(q_tree->ac_l);
    sfRectangleShape_destroy(q_tree->h_b);
    for (cur = q_tree->quad_l->head; cur != NULL; cur = next){
        next = cur->next;
        free(((quad_t_t *)cur->data));
        destroy_nodes(q_tree->quad_l, cur);
    }
    free(q_tree->quad_l);
}
