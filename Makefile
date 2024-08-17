# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 14:59:04 by lopoka            #+#    #+#              #
#    Updated: 2024/08/15 14:27:37 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ofast
MLX42 = sources/MLX42

LIBFTDIR = ./libft
LIBS = $(LIBFTDIR)/libft.a ${MLX42}/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	=	sources/main.c \
			sources/hooks.c \
			sources/init.c \
			sources/show_img.c \
			sources/close.c \
			sources/void_arr.c \
			sources/parser/parser.c \
			sources/parser/validate.c \
			sources/parser/file.c \
			sources/parser/array.c \

OFILES = ${SRCS:.c=.o}

target debug: CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -O1 -g
target debug: CDEBUG = -DDEBUG=1

target symbols: CFLAGS = -Wall -Wextra -Werror -g
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

re: fclean all
debug: clean all
symbols: re

.PHONY: debug, symbols, all, clean, fclean, re, mlx42
