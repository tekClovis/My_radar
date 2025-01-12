/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** set_tower
*/
#include "my.h"
#include "include.h"

tower_t *set_tower(void)
{
    tower_t *tower = malloc(sizeof(tower_t));
    sfIntRect rect = (sfIntRect){0, 0, 400, 400};

    if (tower == NULL)
        return NULL;
    tower->sprite = sfSprite_create();
    tower->h_b = sfCircleShape_create();
    tower->txture = sfTexture_createFromFile("./img/tower.png", &rect);
    sfSprite_setTexture(tower->sprite, tower->txture, sfTrue);
    sfSprite_setOrigin(tower->sprite, (sfVector2f){400 / 2, 400});
    sfCircleShape_setOutlineColor(tower->h_b, sfBlue);
    sfCircleShape_setOutlineThickness(tower->h_b, 1.0);
    sfCircleShape_setFillColor(tower->h_b, sfTransparent);
    return tower;
}
