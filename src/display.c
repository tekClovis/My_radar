/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** display
*/
#include "include.h"

static
void display_tower(list_t *tower_l, sfRenderWindow *window, radar_t *radar)
{
    node_t *current = tower_l->head;

    for (; current != NULL; current = current->next){
        if (radar->a->hit_box)
            sfRenderWindow_drawCircleShape(window,
            ((tower_t *)current->data)->h_b, NULL);
        if (radar->a->sprite)
            sfRenderWindow_drawSprite(window,
            ((tower_t *)current->data)->sprite, NULL);
    }
}

static
void display_ac(list_t *plane_l, sfRenderWindow *w, radar_t *radar)
{
    node_t *cur = plane_l->head;

    for (; cur != NULL; cur = cur->next){
        if (radar->a->hit_box)
            sfRenderWindow_drawRectangleShape(w, ((plane_t *)cur->data)->h_b,
            NULL);
        if (radar->a->sprite)
            sfRenderWindow_drawSprite(w, ((plane_t *)cur->data)->sprite, NULL);
    }
    if (radar->drag_plane == NULL)
        return;
    if (radar->a->hit_box)
        sfRenderWindow_drawRectangleShape(w, radar->drag_plane->h_b, NULL);
    if (radar->a->sprite)
        sfRenderWindow_drawSprite(w, radar->drag_plane->sprite, NULL);
}

void display(radar_t *radar)
{
    sfTime time = sfClock_getElapsedTime(radar->time);
    char *str_time = float_to_str((int)sfTime_asSeconds(time));

    sfRenderWindow_clear(radar->a->w, sfBlack);
    sfRenderWindow_drawSprite(radar->a->w, radar->a->bg_s, NULL);
    display_tower(radar->list->tower_l, radar->a->w, radar);
    display_ac(radar->list->plane_l, radar->a->w, radar);
    sfText_setString(radar->a->time, str_time);
    sfRenderWindow_drawText(radar->a->w, radar->a->time, NULL);
    free(str_time);
}
