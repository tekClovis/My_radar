/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** struct_init
*/
#include "include.h"
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window/Event.h>

radar_t *radar_init(void)
{
    radar_t *radar = malloc(sizeof(radar_t));

    srand(time(NULL));
    radar->list = malloc(sizeof(list_t));
    radar->list->tower_l = list_create();
    radar->list->plane_l = list_create();
    radar->list->in_wait_ac = list_create();
    radar->drag_plane = NULL;
    radar->plane_texture = sfTexture_createFromFile("./img/space_ship.png",
        NULL);
    radar->time = sfClock_create();
    return radar;
}
