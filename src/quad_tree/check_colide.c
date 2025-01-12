/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** check_colide
*/
#include "include.h"

static
void verif_ac_colide(node_t *cur_ac_l, node_t *cur_ac_verif)
{
    if (cur_ac_verif == NULL)
        return;
    for (; cur_ac_verif != NULL; cur_ac_verif = cur_ac_verif->next){
        if (ac_colide(((plane_t *)cur_ac_verif->data),
            ((plane_t *)cur_ac_l->data)) == true){
            ((plane_t *)cur_ac_verif->data)->is_dead = true;
            ((plane_t *)cur_ac_l->data)->is_dead = true;
        }
    }
}

void check_colide(quad_t_t *q_tree, list_t *tower_l, asset_t *a)
{
    node_t *cur_quad_l = q_tree->quad_l->head;
    node_t *cur_ac_l = q_tree->ac_l->head;

    if (a->q_tree == true)
        sfRenderWindow_drawRectangleShape(a->w, q_tree->h_b, NULL);
    for (; cur_quad_l != NULL; cur_quad_l = cur_quad_l->next)
        check_colide(((quad_t_t *)cur_quad_l->data), tower_l, a);
    for (; cur_ac_l != NULL; cur_ac_l = cur_ac_l->next){
        verif_ac_colide(cur_ac_l, cur_ac_l->next);
    }
    destroy_q_tree(q_tree);
}
