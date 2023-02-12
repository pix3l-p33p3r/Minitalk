# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elel-yak <elel-yak@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 13:41:07 by elel-yak          #+#    #+#              #
#    Updated: 2023/02/12 19:16:45 by elel-yak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client
NAME_S_B = server_bonus
NAME_C_B = client_bonus

CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

HEADER = ./inc/minitalk.h

SRC = ./src/ft_utils.c
SRC_S = ./src/server.c
SRC_S_B = ./src/server_bonus.c
SRC_C = ./src/client.c
SRC_C_B = ./src/client_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)
OBJ_S_B = $(SRC_S_B:.c=.o)
OBJ_C_B = $(SRC_C_B:.c=.o)

all:	$(NAME_S) $(NAME_C)

bonus:	$(NAME_S_B) $(NAME_C_B)

$(NAME_S):	$(OBJ) $(OBJ_S)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_S) -o $(NAME_S)

$(NAME_C):	$(OBJ) $(OBJ_C)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_C) -o $(NAME_C)

$(NAME_S_B):	$(OBJ) $(OBJ_S_B)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_S_B) -o $(NAME_S_B)

$(NAME_C_B):	$(OBJ) $(OBJ_C_B)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_C_B) -o $(NAME_C_B)

%.o:	%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:	
	$(RM) $(OBJ) $(OBJ_S) $(OBJ_C) $(OBJ_S_B) $(OBJ_C_B)

fclean:	clean
	$(RM) $(NAME_S) $(NAME_C) $(NAME_S_B) $(NAME_C_B)

re: fclean all
