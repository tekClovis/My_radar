/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** check_in_wait
*/
#include "include.h"

void check_in_wait(list_t *plane_l, list_t *in_wait, sfClock *clock)
{
    node_t *cur = in_wait->head;
    node_t *next = NULL;
    sfTime time = sfClock_getElapsedTime(clock);

    for (; cur != NULL; cur = next){
        next = cur->next;
        if ((int)((plane_t *)cur->data)->t_spawn < sfTime_asMicroseconds(time)
            / 1000000){
            push_back(plane_l, cur->data);
            destroy_nodes(in_wait, cur);
        }
    }
}
