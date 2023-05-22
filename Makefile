# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 11:20:10 by jbok              #+#    #+#              #
#    Updated: 2023/04/20 18:43:09 by jbok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

HEADER = minirt.h ft_deque.h ft_vector.h ft_treemap.h
HEADER := ${addprefix ./include/, ${HEADER}}
SRC = main.c init.c trace.c light.c color_basic.c color_self.c
SRC += parse.c parse_obj.c parse_obj2.c parse_get.c
SRC += minirt_utils.c multi.c solutions.c det.c ft_split2.c
SRC += vec_basic.c vec_self.c vec_utils.c ft_deque.c ft_vector.c key_hook.c
SRC += ft_treemap_insert.c ft_treemap_del.c ft_treemap_balance.c
SRC += ft_treemap_traversal.c ft_treemap_utils.c
SRC += rt.c rt_utils.c ambient.c set_uv.c refresh.c del.c
OBJ = ${addprefix obj/, ${SRC:.c=.o}}
INCLUDE = ./include ./mlx ./libft

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

CFLAGS = -Wall -Wextra -Werror -O2
CFLAGS += ${addprefix -I, ${INCLUDE}}
LINKFLAGS = -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

all:	${NAME}

bonus:	${NAME}

${NAME}:	${OBJ} ${MLX} ${LIBFT}
	${CC} ${CFLAGS} ${LINKFLAGS} ${OBJ} -o $@

obj/%.o:	src/%.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	$(MAKE) -C libft

${MLX}:
	${MAKE} -C mlx

clean:
	${MAKE} -C mlx clean
	${MAKE} -C libft clean
	${RM} ${OBJ}

fclean:
	${MAKE} clean
	${MAKE} -C libft fclean
	${RM} ${NAME}

re:
	${MAKE} fclean
	${MAKE} all

.PHONY:	all clean fclean re bonus
