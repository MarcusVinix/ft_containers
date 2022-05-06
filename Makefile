PATH_INCLUDES = ./includes

NAME = main

CC = c++
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -I $(PATH_INCLUDES) main.cpp -o $(NAME)

clean:
	$(RM) $(NAME)

re: clean all