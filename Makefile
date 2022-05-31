NAME = ft_containers
PATH_INCLUDES = ./includes
PATH_ITERATORS = ./iterators
PATH_CONTAINERS = ./containers
PATH_SRC = ./src/
PATH_OBJ = ./obj/
INCLUDES = -I $(PATH_INCLUDES) -I $(PATH_ITERATORS) -I $(PATH_CONTAINERS)

SRC = $(addprefix $(PATH_SRC), main.cpp)
OBJ = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))

CC = c++
CFLAGS = -Werror -Wextra -Wall -std=c++98
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(PATH_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
