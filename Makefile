# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 14:59:04 by lopoka            #+#    #+#              #
#    Updated: 2024/09/05 17:50:30 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += -j4
NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror
MLX42 = ./MLX42

LIBFTDIR = ./libft
LIBS = $(LIBFTDIR)/libft.a ${MLX42}/build/libmlx42.a -ldl -lglfw -pthread -lm

SOURCE_DIR = sources
SOURCES	=	main.c \
			hooks.c \
			init.c \
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
			intersections/intersections_arr.c \
			camera.c \
			scene.c \
			render.c \
			thread.c \
			worker.c \
			heap_sort.c \
			obj_transforms.c \
			prep_comps1.c \
			prep_comps2.c \
			obj_normals.c \
			get_test_scene.c \
			phong.c \
			get_color.c \

PARSER_DIR = sources/parser
PARSER_SRC = parser.c parser_utils.c validate.c file.c array.c \
			fill.c ft_atof.c identifier.c obj.c camera.c light.c
PARSER_OBJ = $(addprefix $(PARSER_DIR)/,$(PARSER_SRC:.c=.o))

BVH_DIR = sources/bvh
BVH_SRC = bvh.c bvh_intersect.c bvh_utils.c bounds.c node.c aabb.c split.c 
BVH_OBJ = $(addprefix $(BVH_DIR)/,$(BVH_SRC:.c=.o))

OFILES = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
OFILES += $(PARSER_OBJ) $(BVH_OBJ)

target debug: CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -O1 -g
target debug: CDEBUG = -DDEBUG=1

target symbols: CFLAGS = -Wall -Wextra -Werror -gdwarf-4
target symbols: CDEBUG = -DDEBUG=1

target fast: CFLAGS += -O2
target fastmath: CFLAGS += -O2 -ffast-math
target profile:	CFLAGS += -O2 -fno-math-errno -fno-trapping-math -gdwarf-4

export CFLAGS

all : mandatory

mandatory : .mandatory

bonus : .bonus

%.o: %.c
	${CC} ${CFLAGS} -I./includes -c -o $@ $<

.mandatory : ${OFILES}
	cmake ${MLX42} -B ${MLX42}/build $(CDEBUG) && make -C ${MLX42}/build -j4
	$(MAKE) -C $(LIBFTDIR)
	${CC} -o ${NAME} ${CFLAGS} ${OFILES} ${LIBS}
	@touch .mandatory
	@rm -f .bonus

.bonus : ${B_OFILES}
	cmake ${MLX42} -B ${MLX42}/build $(CDEBUG) && make -C ${MLX42}/build -j4
	$(MAKE) -C $(LIBFTDIR)
	${CC} -o ${NAME} ${CFLAGS} ${B_OFILES} ${LIBS}
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

.PHONY: debug, debug_clean, symbols, fast, fastmath, profile, all, clean, fclean, re, mlx42
