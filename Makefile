# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 14:59:04 by lopoka            #+#    #+#              #
#    Updated: 2024/08/24 18:21:50 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += -j4
NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror -O2
MLX42 = sources/MLX42

LIBFTDIR = ./libft
LIBS = $(LIBFTDIR)/libft.a ${MLX42}/build/libmlx42.a -ldl -lglfw -pthread -lm

SOURCE_DIR = sources
SOURCES	=	main.c \
			hooks.c \
			init.c \
			close.c \
			void_arr.c \
			vct_math.c \
			mtrx_math.c \
			mtrx_transform.c \
			camera.c \
			scene.c \
			render.c \
			thread.c \
			worker.c \
			shapes.c \
			get_test_scene.c \
			colour.c \
			intersections.c \

PARSER_DIR = sources/parser
PARSER_SRC = parser.c parser_utils.c validate.c file.c array.c \
			fill.c ft_atof.c identifier.c shape.c camera.c light.c
PARSER_OBJ = $(addprefix $(PARSER_DIR)/,$(PARSER_SRC:.c=.o))

OFILES = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
OFILES += $(PARSER_OBJ)

target debug: CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -O1 -g
target debug: CDEBUG = -DDEBUG=1

target symbols: CFLAGS = -Wall -Wextra -Werror -gdwarf-4
target symbols: CDEBUG = -DDEBUG=1


export CFLAGS

all : mandatory

mandatory : .mandatory

bonus : .bonus

%.o: %.c
	${CC} ${CFLAGS} -I./includes -c -o $@ $<

.mandatory : ${OFILES}
	cmake ${MLX42} -B ${MLX42}/build $(CDEBUG) && make -C ${MLX42}/build -j4
	$(MAKE) -C $(LIBFTDIR)
	${CC} -o ${NAME} ${CFLAGS} -pthread ${OFILES} ${LIBS}
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

.PHONY: debug, debug_clean, symbols, all, clean, fclean, re, mlx42
