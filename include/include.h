/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** include
*/
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window/Event.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "my.h"

#ifndef INCLUDE_H
    #define INCLUDE_H

typedef struct quad_t_s {
    sfFloatRect zone;
    sfRectangleShape *h_b;
    list_t *ac_l;
    list_t *quad_l;
    int capacity;
    bool is_div;
} quad_t_t;

typedef struct plane_s {
    sfVector2f pos;
    sfVector2f pos_e;
    float speed;
    float t_spawn;
    sfRectangleShape *h_b;
    sfSprite *sprite;
    bool is_dead;
} plane_t;

typedef struct tower_s {
    sfVector2f pos;
    sfCircleShape *h_b;
    sfTexture *txture;
    sfSprite *sprite;
} tower_t;

typedef struct list_r_s {
    list_t *in_wait_ac;
    list_t *tower_l;
    list_t *plane_l;
} list_r_t;

typedef struct asset_s {

    sfRenderWindow *w;
    sfTexture *bg_t;
    sfSprite *bg_s;
    sfFont *font;
    sfText *time;
    bool q_tree;
    bool sprite;
    bool hit_box;
} asset_t;

typedef struct radar_s {
    asset_t *a;
    list_r_t *list;
    quad_t_t *q_tree;
    sfTexture *plane_texture;
    sfClock *time;
    plane_t *drag_plane;
} radar_t;


radar_t *radar_init(void);
int push_front(list_t *list, void *data);
int push_back(list_t *list, void *data);
int destroy_nodes(list_t *list, node_t *current);
int parsing(char *av, radar_t *radar);
quad_t_t *set_quad_tree(sfFloatRect zone);
void insert(quad_t_t *q_tree, plane_t *plane, list_t *tower_l);
void sub_divise(quad_t_t *q_tree);
asset_t *set_asset(void);
tower_t *set_tower(void);
plane_t *plane_init(sfTexture *texture);
bool check_in(quad_t_t *quad_t, plane_t *plane);
void destroy_plane(plane_t *plane);
bool is_in_tower(plane_t *plane, list_t *tower_l);
bool ac_colide(plane_t *plane1, plane_t *plane2);
void check_colide(quad_t_t *q_tree, list_t *tower_l, asset_t *a);
void destroy_q_tree(quad_t_t *q_tree);
void check_in_wait(list_t *plane_l, list_t *in_wait, sfClock *clock);
void plane_l_update(list_t *plane_l, radar_t *radar);
void display(radar_t *radar);
void check_event(radar_t *radar);
void grab_plane(float mouse_x, float mouse_y, radar_t *radar);
void move_drag(int mouse_x, int mouse_y, plane_t *drag_plane);
void drop_plane(radar_t *radar);
bool check_end(list_t *plane_l, list_t *in_wait_plane, plane_t *drag_plane);
bool is_in_window(plane_t *plane);

#endif /* INCLUDE_H_ */
