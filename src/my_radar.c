/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** my_radar
*/
#include "include.h"

static
void destroy_tower(list_t *tower_l)
{
    node_t *cur = tower_l->head;
    node_t *next = NULL;

    for (; cur != NULL; cur = next){
        next = cur->next;
        sfCircleShape_destroy(((tower_t *)cur->data)->h_b);
        sfSprite_destroy(((tower_t *)cur->data)->sprite);
        sfTexture_destroy(((tower_t *)cur->data)->txture);
        free(((tower_t *)cur->data));
        destroy_nodes(tower_l, cur);
    }
    free(tower_l);
}

static
void destroy_asset(asset_t *asset)
{
    sfSprite_destroy(asset->bg_s);
    sfTexture_destroy(asset->bg_t);
    sfFont_destroy(asset->font);
    sfText_destroy(asset->time);
    sfRenderWindow_destroy(asset->w);
}

static
void destroy_plane_l(list_t *plane_l)
{
    node_t *cur = plane_l->head;
    node_t *next = NULL;

    for (; cur != NULL; cur = next){
        next = cur->next;
        destroy_plane((plane_t *)cur->data);
        destroy_nodes(plane_l, cur);
    }
    free(plane_l);
}

void destroy_all(radar_t *radar)
{
    destroy_plane_l(radar->list->in_wait_ac);
    destroy_plane_l(radar->list->plane_l);
    destroy_tower(radar->list->tower_l);
    destroy_asset(radar->a);
    if (radar->q_tree != NULL)
        free(radar->q_tree);
    if (radar->drag_plane != NULL)
        destroy_plane(radar->drag_plane);
    sfTexture_destroy(radar->plane_texture);
    sfClock_destroy(radar->time);
    free(radar->list);
    free(radar->a);
    free(radar);
}

void while_open(radar_t *radar)
{
    if (check_end(radar->list->plane_l, radar->list->in_wait_ac,
        radar->drag_plane))
        sfRenderWindow_close(radar->a->w);
    check_event(radar);
    display(radar);
    check_in_wait(radar->list->plane_l, radar->list->in_wait_ac, radar->time);
    plane_l_update(radar->list->plane_l, radar);
    check_colide(radar->q_tree, radar->list->tower_l, radar->a);
    sfRenderWindow_display(radar->a->w);
    free(radar->q_tree);
    radar->q_tree = NULL;
    if (radar->drag_plane == NULL)
        return;
    if (is_in_window(radar->drag_plane) == false){
        destroy_plane(radar->drag_plane);
        radar->drag_plane = NULL;
    }
}

int main(int ac, char **av)
{
    radar_t *radar = radar_init();
    int pars_code = 0;

    if (ac != 2)
        return 84;
    pars_code = parsing(av[1], radar);
    if (pars_code == 84)
        return 84;
    if (pars_code == 1){
        mini_printf("%s\n", my_catchar("./scripts/usage"));
        return 1;
    }
    radar->a = set_asset();
    while (sfRenderWindow_isOpen(radar->a->w))
        while_open(radar);
    destroy_all(radar);
    return 0;
}
