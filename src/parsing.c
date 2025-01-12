/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** parsing
*/
#include "include.h"
#include <math.h>

static
void set_rotation(plane_t *plane)
{
    float ang = atan2f(plane->pos.y - plane->pos_e.y,
        plane->pos.x - plane->pos_e.x);
    float pi = 3.14;
    float deg = ang * (180.f / pi);
    sfVector2f r_size = {20, 20};

    sfSprite_setPosition(plane->sprite, plane->pos);
    sfSprite_setOrigin(plane->sprite, (sfVector2f){1024 / 2, 1024 / 2});
    sfSprite_setRotation(plane->sprite, deg);
    sfRectangleShape_setOrigin(plane->h_b, (sfVector2f){10, 10});
    sfRectangleShape_setPosition(plane->h_b, plane->pos);
    sfRectangleShape_setSize(plane->h_b, r_size);
}

static
int pars_plane(char **tab, radar_t *radar)
{
    int i = 0;
    plane_t *plane = plane_init(radar->plane_texture);

    for (i = 0; tab[i] != NULL && plane != NULL; i++)
        if (is_float(tab[i]) == 0)
            return 84;
    if (i != 6)
        return 84;
    plane->pos = (sfVector2f){get_float(tab[0]), get_float(tab[1])};
    plane->pos_e = (sfVector2f){get_float(tab[2]), get_float(tab[3])};
    plane->speed = get_float(tab[4]);
    plane->t_spawn = get_float(tab[5]);
    set_rotation(plane);
    if (plane->t_spawn == 0){
        push_back(radar->list->plane_l, plane);
        return 0;
    }
    push_back(radar->list->in_wait_ac, plane);
    return 0;
}

static
sfVector2f get_n_pos(tower_t *tower)
{
    float rad = sfCircleShape_getRadius(tower->h_b);
    sfVector2f n_pos = {-1920.0, -1080.0};

    if (tower->pos.x + rad > 1920 && tower->pos.y + rad > 1080)
        n_pos = (sfVector2f){tower->pos.x - 1920, tower->pos.y - 1080};
    if (tower->pos.x + rad > 1920 && tower->pos.y + rad <= 1080)
        n_pos = (sfVector2f){tower->pos.x - 1920, tower->pos.y};
    if (tower->pos.x + rad <= 1920 && tower->pos.y + rad > 1080)
        n_pos = (sfVector2f){tower->pos.x, tower->pos.y - 1080};
    if (tower->pos.x - rad < 0 && tower->pos.y - rad < 0)
        n_pos = (sfVector2f){tower->pos.x + 1920, tower->pos.y + 1080};
    if (tower->pos.x - rad < 0 && tower->pos.y - rad >= 0)
        n_pos = (sfVector2f){tower->pos.x + 1920, tower->pos.y};
    if (tower->pos.x - rad >= 0 && tower->pos.y - rad < 0)
        n_pos = (sfVector2f){tower->pos.x, tower->pos.y + 1080};
    return n_pos;
}

static
tower_t *is_in_corner_tower(tower_t *tower)
{
    tower_t *n_tower = NULL;
    sfVector2f n_pos = get_n_pos(tower);
    float rad = sfCircleShape_getRadius(tower->h_b);

    if (n_pos.x == -1920.0 && n_pos.y == -1080.0)
        return NULL;
    n_tower = set_tower();
    n_tower->pos = n_pos;
    sfCircleShape_setOrigin(n_tower->h_b,
        sfCircleShape_getOrigin(tower->h_b));
    sfCircleShape_setRadius(n_tower->h_b, rad);
    sfCircleShape_setPosition(n_tower->h_b, n_tower->pos);
    sfSprite_setScale(n_tower->sprite, (sfVector2f){0.015 * (rad / 2),
        0.015 * (rad / 2)});
    sfSprite_setPosition(n_tower->sprite, n_tower->pos);
    return n_tower;
}

static
int pars_tower(char **tab, list_t *tower_l)
{
    int i = 0;
    tower_t *tower = set_tower();

    for (i = 0; tab[i] != NULL && tower != NULL; i++)
        if (is_float(tab[i]) == 0)
            return 84;
    if (i != 3 || get_float(tab[0]) > 1920.0 || get_float(tab[0]) < 0.0 ||
        get_float(tab[1]) > 1080.0 || get_float(tab[1]) < 0.0)
        return 84;
    tower->pos = (sfVector2f){get_float(tab[0]), get_float(tab[1])};
    sfCircleShape_setRadius(tower->h_b, get_float(tab[2]) * 2.0);
    sfCircleShape_setOrigin(tower->h_b, (sfVector2f){get_float(tab[2]) * 2.0,
        get_float(tab[2]) * 2.0});
    sfCircleShape_setPosition(tower->h_b, tower->pos);
    sfSprite_setScale(tower->sprite, (sfVector2f){0.015 * get_float(tab[2]),
        0.015 * get_float(tab[2])});
    sfSprite_setPosition(tower->sprite, tower->pos);
    push_back(tower_l, tower);
    push_back(tower_l, is_in_corner_tower(tower));
    return 0;
}

int choose_between_a_t(char **args, radar_t *radar)
{
    char **ligne = NULL;
    int err = 0;

    for (int i = 0; args[i] != NULL; i++){
        ligne = my_str_to_word_array(args[i], "\t ");
        if (ligne[0][0] == 'A')
            err = pars_plane(&ligne[1], radar);
        if (ligne[0][0] == 'T')
            err = pars_tower(&ligne[1], radar->list->tower_l);
        if ((ligne[0][0] != 'T' && ligne[0][0] != 'A') ||
            my_strlen(ligne[0]) != 1){
            my_putstrerr("wrongletter suppose to be A or T\n");
            return 84;
        }
        if (err == 84)
            return 84;
        free_array(ligne);
    }
    return 0;
}

int parsing(char *av, radar_t *radar)
{
    char *file = my_catchar(av);
    char **args = NULL;

    if (my_strcmp(av, "-h") == 0)
        return 1;
    if (file == NULL)
        return 84;
    args = my_str_to_word_array(file, "\r\n");
    if (args == NULL || choose_between_a_t(args, radar) == 84)
        return 84;
    free_array(args);
    free(file);
    return 0;
}
