/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** check_event
*/
#include "include.h"

bool check_end(list_t *plane_l, list_t *in_wait_plane, plane_t *drag_plane)
{
    if (plane_l->size == 0 && in_wait_plane->size == 0 && drag_plane == NULL)
        return true;
    return false;
}

static
void handle_keyboard_evt(sfEvent e, radar_t *radar)
{
    if ((e.type == sfEvtKeyPressed && e.key.code == sfKeyEscape)
        || e.type == sfEvtClosed)
        sfRenderWindow_close(radar->a->w);
    if ((e.type == sfEvtKeyPressed && e.key.code == sfKeyS))
        radar->a->sprite = !radar->a->sprite;
    if ((e.type == sfEvtKeyPressed && e.key.code == sfKeyL))
        radar->a->hit_box = !radar->a->hit_box;
    if ((e.type == sfEvtKeyPressed && e.key.code == sfKeyQ))
        radar->a->q_tree = !radar->a->q_tree;
}

void check_event(radar_t *radar)
{
    sfEvent e;

    while (sfRenderWindow_pollEvent(radar->a->w, &e)) {
        handle_keyboard_evt(e, radar);
        if (e.mouseButton.type == sfEvtMouseMoved &&
            radar->drag_plane != NULL)
            move_drag(e.mouseMove.x, e.mouseMove.y,
            radar->drag_plane);
        if (e.mouseButton.type == sfEvtMouseButtonPressed &&
            e.mouseButton.button == sfMouseLeft &&
            radar->drag_plane == NULL)
            grab_plane((float)e.mouseButton.x, (float)e.mouseButton.y, radar);
        if (e.mouseButton.type == sfEvtMouseButtonReleased
            && e.mouseButton.button == sfMouseLeft &&
            radar->drag_plane != NULL){
            drop_plane(radar);
        }
    }
}
