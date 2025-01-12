/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** set_plane
*/
#include "my.h"
#include "include.h"

plane_t *plane_init(sfTexture *texture)
{
    plane_t *plane = malloc(sizeof(plane_t));
    sfVector2f scale = {0.02, 0.02};

    if (plane == NULL)
        return NULL;
    plane->h_b = sfRectangleShape_create();
    plane->speed = 0;
    plane->t_spawn = 0;
    plane->is_dead = false;
    plane->sprite = sfSprite_create();
    sfSprite_setTexture(plane->sprite, texture, sfTrue);
    sfSprite_setScale(plane->sprite, scale);
    sfRectangleShape_setOutlineThickness(plane->h_b, 1.0);
    sfRectangleShape_setOutlineColor(plane->h_b, sfRed);
    sfRectangleShape_setFillColor(plane->h_b, sfTransparent);
    return plane;
}
