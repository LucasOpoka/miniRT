# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 14:59:04 by lopoka            #+#    #+#              #
#    Updated: 2024/09/18 18:14:45 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += -j4
NAME = miniRT

CC = cc

CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -Iinclude
MLX42 := ./MLX42

LIBFTDIR = ./libft
LIBS = $(LIBFTDIR)/libft.a ${MLX42}/build/libmlx42.a -ldl -lglfw -pthread -lm

SOURCE_DIR = sources
SOURCES	=	main.c \
			void_arr.c \
			operations/point.c \
			operations/vct1.c \
			operations/vct2.c \
			operations/mtrx1.c \
			operations/mtrx2.c \
			operations/mtrx3.c \
			operations/clr1.c \
			operations/clr2.c \
			intersections/intersections.c \
			intersections/cylinder.c \
			intersections/triangle.c \
			intersections/cone.c \
			intersections/intersections_arr.c \
			patterns/uv1.c \
			patterns/uv2.c \
			patterns/patterns.c \
			patterns/texture_and_bump.c \
			camera.c \
			scene.c \
			heap_sort.c \
			obj_transforms.c \
			prep_comps1.c \
			prep_comps2.c \
			obj_normals1.c \
			obj_normals2.c \
			get_test_scene.c \
			phong.c \
			get_color.c \

PARSER_DIR = sources/parser
PARSER_SRC = parser.c parser_utils.c validate.c file.c array.c \
	     fill.c ft_atof.c identifier.c obj.c camera.c \
	     light.c id.c obj_add.c
PARSER_OBJ = $(addprefix $(PARSER_DIR)/,$(PARSER_SRC:.c=.o))

PARSER_SRC_BONUS = parser.c parser_utils.c validate.c file.c array.c \
	     fill.c ft_atof.c identifier.c obj.c camera.c \
	     bonus/light_bonus.c bonus/id_bonus.c \
	     bonus/obj_add_bonus.c bonus/obj_bonus.c
PARSER_OBJ_BONUS= $(addprefix $(PARSER_DIR)/,$(PARSER_SRC_BONUS:.c=.o))

RENDER_DIR = sources/render
RENDER_SRC = init.c render.c hooks.c
RENDER_OBJ = $(addprefix $(RENDER_DIR)/,$(RENDER_SRC:.c=.o))

RENDER_BONUS_DIR = sources/render_bonus
RENDER_BONUS_SRC = init.c render.c hooks.c thread.c worker.c
RENDER_BONUS_OBJ = $(addprefix $(RENDER_BONUS_DIR)/,$(RENDER_BONUS_SRC:.c=.o))

PPM_DIR = sources/ppm
PPM_SRC = ppm.c ppm_matrix.c header.c
PPM_OBJ = $(addprefix $(PPM_DIR)/,$(PPM_SRC:.c=.o))

BVH_DIR = sources/bvh
BVH_SRC = bvh.c bvh_intersect.c bvh_utils.c bounds.c bounds_obj.c node.c aabb.c split.c
BVH_OBJ = $(addprefix $(BVH_DIR)/,$(BVH_SRC:.c=.o))


OFILES = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
OFILES += $(PARSER_OBJ) $(PPM_OBJ) $(BVH_OBJ) $(RENDER_OBJ)
MANDATORY_SRC = $(OFILES:.o=.c)

B_OFILES = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
B_OFILES += $(PARSER_OBJ_BONUS) $(PPM_OBJ) $(BVH_OBJ) $(RENDER_BONUS_OBJ)
BONUS_SRC = $(B_OFILES:.o=.c)

target debug: CFLAGS += -fsanitize=address,undefined -g
target debug: CDEBUG = -DDEBUG=1

target debug_bonus: CFLAGS += -fsanitize=address,undefined -g
target debug_bonus: CDEBUG = -DDEBUG=1

target fast_bonus: CFLAGS += -O2 -ffast-math

target symbols: CFLAGS = -Wall -Wextra -Werror -gdwarf-4
target symbols: CDEBUG = -DDEBUG=1

target fast: CFLAGS += -O2
target fastmath: CFLAGS += -O2 -ffast-math
target profile:	CFLAGS += -O2 -fno-math-errno -fno-trapping-math -gdwarf-4

export CFLAGS

all : mandatory

mandatory : .mandatory
bonus : .bonus

$OFILES: $(MANDATORY_SRC)
	${CC} ${CFLAGS} -c -o $@ $<

$B_OFILES: $(BONUS_SRC)
	${CC} ${CFLAGS} -c -o $@ $<

.mandatory : ${OFILES}
	cmake ${MLX42} -B ${MLX42}/build $(CDEBUG) && make -C ${MLX42}/build -j4
	$(MAKE) -C $(LIBFTDIR)
	${CC} -o ${NAME} ${CFLAGS} $(LDFLAGS) ${OFILES} ${LIBS}
	@rm -f .bonus
	@touch .mandatory

.bonus : ${B_OFILES}
	cmake ${MLX42} -B ${MLX42}/build $(CDEBUG) && make -C ${MLX42}/build -j4
	$(MAKE) -C $(LIBFTDIR)
	${CC} -o ${NAME} ${CFLAGS} $(LDFLAGS) ${B_OFILES} ${LIBS}
	@touch .bonus
	@rm -f .mandatory

clean:
	rm -rf ${OFILES} ${B_OFILES} ${MLX42}/build
	$(MAKE) -C $(LIBFTDIR) $@
	@rm -f .bonus .mandatory

fclean: clean
	rm -rf ${NAME} ${OFILES} ${B_OFILES} ${MLX42}/build
	@rm -f .bonus .mandatory

debug_clean:
	rm -rf ${NAME} ${OFILES} ${B_OFILES}
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
debug: debug_clean all
symbols: re
fast: re
fastmath: re
profile: re
debug_bonus: fclean bonus
fast_bonus: fclean bonus

.PHONY: debug, debug_clean, symbols, fast fastmath, profile \
	debug_bonus, fast_bonus \
	bonus, all, clean, fclean, re, mlx42
