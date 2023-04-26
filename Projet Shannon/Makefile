NAME = jeu_de_shannon

SRCS = sources/clist.c sources/graph.c sources/ia.c sources/shannon.c
INCLUDES = includes/shannon.h

CC = gcc
FLAGS = -Werror -Wextra -Wall


$(NAME): $(SRCS)
		$(CC) $(FLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

clean :
		@rm -f $(NAME)

re : clean all

.PHONY: all clean re