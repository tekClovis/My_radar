##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

NAME = my_radar

SRCS =  src/my_radar.c					\
	src/parsing.c 						\
	src/display.c 						\
	src/check_event.c					\
	src/set_struct/radar_init.c			\
	src/set_struct/set_tower.c 			\
	src/set_struct/set_asset.c			\
	src/quad_tree/insert.c 				\
	src/quad_tree/sub_divise.c 			\
	src/quad_tree/check_colide.c		\
	src/quad_tree/destroy_q_tree.c 		\
	src/quad_tree/set_quad_tree.c 		\
	src/plane/check_in_wait.c 			\
	src/plane/destroy_plane.c 			\
	src/plane/plane_update.c 			\
	src/plane/set_plane.c				\
	src/plane/drag_functions.c 			\
	src/colide_func/is_in_tower.c		\
	src/colide_func/ac_colide.c 		\

CFLAGS = -Wall -Wextra -I ./include

CSFMLFLAGS = -l csfml-window -l csfml-graphics \
	-l csfml-system -l csfml-audio -lm

all :
	make -C ./lib
	gcc -o $(NAME) $(SRCS) $(CFLAGS) $(CSFMLFLAGS) -L ./lib -lmy
clean:
	rm -f $(NAME)

fclean: clean
	make fclean -C ./lib
	rm -rf ./*~

unit_tests:	fclean $(NAME)
	gcc -o unit_tests tests/*.c -L./ -lmy -I./include --coverage -lcriterion

tests_run:	unit_tests
	./unit_tests

debug: CFLAGS += -g
debug: fclean all

re : fclean all
