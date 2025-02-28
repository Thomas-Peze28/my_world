##
## EPITECH PROJECT, 2023
## makefile
## File description:
## my_ls
##

SRC	=	src/main.c			\
		src/open_window.c	\
		src/my_destroy.c	\
		src/create_struct.c	\
		src/rotations.c	\
		src/draw_map.c \
		src/zoom_map.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	window

CFLAGS = -Wextra -Wall -I ./include -l csfml-graphics -l csfml-system \
	-l csfml-window -l csfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all
