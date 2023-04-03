# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 17:26:22 by hlesny            #+#    #+#              #
#    Updated: 2023/03/22 21:42:14 by hlesny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3

MLXFLAGS = -lXext -lX11 -lm
MLXDIR = ./minilibx_linux/
MLX = ./minilibx_linux/libmlx_Linux.a

LIBFTDIR = ./mylibft/
LIBFT = ./mylibft/libft.a

LIBS = $(MLX) $(LIBFT)

SRCDIR = ./srcs/
INCDIR = ./incs/
OBJDIR = ./objs/

SRCS = 	get_next_line.c get_next_line_utils.c ft_atoi.c \
		fdf.c get_map.c get_map_utils.c \
		draw_map.c draw_utils.c draw_utils2.c \
		pixels_gradient.c points_gradient.c \
		events.c events2.c \
		destroy.c utils.c

INC_FILES = fdf.h get_next_line.h hooks.h colors.h
INCLUDES = $(addprefix $(INCDIR), $(INC_FILES))
		
OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

export C_INCLUDE_PATH = $(INCDIR):$(MLXDIR):$(LIBFTDIR)
export LIBRARY_PATH = $(MLXDIR):$(LIBFTDIR)

all : $(LIBS) $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $@ $^ $(MLX) $(MLXFLAGS) $(LIBFT)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS) :
	make -C $(MLXDIR)
	make -C $(LIBFTDIR)

clean : 
	$(RM) $(OBJS) -r $(OBJDIR)
	make clean -C $(MLXDIR)
	make clean -C $(LIBFTDIR)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)

re : fclean all

.PHONY:
	all re clean fclean

