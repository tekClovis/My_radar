/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** set_window
*/
#include "my.h"
#include "include.h"

asset_t *set_asset(void)
{
    asset_t *asset = malloc(sizeof(asset_t));
    sfVideoMode zone = {1920, 1080, 32};

    if (asset == NULL)
        return NULL;
    asset->w = sfRenderWindow_create(zone, "My_radar", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(asset->w, 60);
    asset->bg_s = sfSprite_create();
    asset->bg_t = sfTexture_createFromFile("./img/bg.png", NULL);
    sfSprite_setTexture(asset->bg_s, asset->bg_t, sfTrue);
    asset->hit_box = true;
    asset->sprite = true;
    asset->q_tree = true;
    asset->time = sfText_create();
    asset->font = sfFont_createFromFile("antonio/Antonio-Bold.ttf");
    sfSprite_setPosition(asset->bg_s, (sfVector2f){0, 0});
    sfText_setPosition(asset->time, (sfVector2f){1800, 20});
    sfText_setFont(asset->time, asset->font);
    sfText_setString(asset->time, "0\0");
    return asset;
}
