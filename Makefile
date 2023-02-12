# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elel-yak <elel-yak@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 13:41:07 by elel-yak          #+#    #+#              #
#    Updated: 2023/02/12 13:28:31 by elel-yak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
NAME_C = client
NAME_B = serverb
NAME_B_C = clientb

CC = gcc
# FLAGS = -Wall -Werror -Wextra
RM = rm -rf

HEADER = ./inc/minitalk.h

SRC = ./src/ft_utils.c
SRC_S = ./src/server.c
SRC_S_B = ./src/server_bonus.c
SRC_C = ./src/client.c
SRC_C_B = ./src/client_bonus.c

OBJ = $(patsubst %.c,%.o,$(SRC))
OBJ_S = $(patsubst %.c,%.o,$(SRC_S))
OBJ_C = $(patsubst %.c,%.o,$(SRC_C))
OBJ_S_B = $(patsubst %.c,%.o,$(SRC_S_B))
OBJ_C_B = $(patsubst %.c,%.o,$(SRC_C_B))

all:	$(NAME) $(NAME_C)

bonus:	$(NAME_B) $(NAME_B_C)

$(NAME):	$(OBJ) $(OBJ_S)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_S) -o $(NAME)

$(NAME_C):	$(OBJ) $(OBJ_C)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_C) -o $(NAME_C)

$(NAME_B):	$(OBJ) $(OBJ_S_B)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_S_B) -o $(NAME_B)

$(NAME_B_C):	$(OBJ) $(OBJ_S_B) $(OBJ_C_B)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_C_B) -o $(NAME_B_C)

%.o:	%.c Makefile $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:	
	$(RM) $(OBJ) $(OBJ_S) $(OBJ_C) $(OBJ_S_B) $(OBJ_C_B)

fclean:	clean
	$(RM) server client serverb clientb

re: fclean all
