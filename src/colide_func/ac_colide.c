/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** ac_colide
*/
#include "my.h"
#include "include.h"
#include <math.h>

bool ac_colide(plane_t *plane1, plane_t *plane2)
{
    sfVector2f s_p1 = {0, 0};
    sfVector2f s_p2 = {0, 0};

    if (plane1 == NULL || plane2 == NULL || plane1 == plane2)
        return false;
    s_p1 = sfRectangleShape_getSize(plane1->h_b);
    s_p2 = sfRectangleShape_getSize(plane2->h_b);
    if ((plane1->pos.x <= plane2->pos.x + s_p2.x) &&
        (plane1->pos.x + s_p1.x >= plane2->pos.x) &&
        (plane1->pos.y <= plane2->pos.y + s_p2.y) &&
        (plane1->pos.y + s_p1.y >= plane2->pos.y))
        return true;
    return false;
}
