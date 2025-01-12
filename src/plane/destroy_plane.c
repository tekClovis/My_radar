/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** destroy_plane
*/
#include "my.h"
#include "include.h"

void destroy_plane(plane_t *plane)
{
    sfRectangleShape_destroy(plane->h_b);
    sfSprite_destroy(plane->sprite);
    free(plane);
}
