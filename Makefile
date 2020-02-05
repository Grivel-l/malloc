# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/11 16:25:45 by legrivel     #+#   ##    ##    #+#        #
#    Updated: 2019/12/06 21:30:34 by legrivel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libmalloc.so
SRCS = free.c malloc.c print.c realloc.c utils.c calloc.c
OBJS = $(SRCS:.c=.o)
SRCS_PATH = ./srcs/
INCS_PATH = ./includes/
LIB_PATH = ./libft/
FLAGS = -Wall -Wextra -Werror -Ofast
CC = /usr/bin/gcc

all: $(NAME)

$(NAME): $(LIB_PATH) $(OBJS)
	$(CC) $(FLAGS) -shared -o $(NAME) $(OBJS) $(LIB_PATH)libft.a

$(LIB_PATH): $(LIB_PATH)libft.a

$(LIB_PATH)libft.a:
	make -C $(LIB_PATH)

%.o: $(SRCS_PATH)%.c $(INCS_PATH)malloc.h
	$(CC) $(FLAGS) -I $(INCS_PATH) -c $<

clean:
	make -C $(LIB_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIB_PATH) fclean
	rm -f $(NAME)

re: fclean all
