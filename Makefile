#Hello

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIB = -lreadline
	INCLUDE = -I
else
	LIB = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
	INCLUDE = -I /Users/$(USER)/.brew/opt/readline/include
endif

NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
HEADER = includes
SRC = sources
OBJ = objects
SOURCES = main.c \
		utils_1.c
SRCS = $(addprefix $(SRC)/, $(SOURCES))
OBJS = $(addprefix $(OBJ)/, $(SOURCES:.c=.o))

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) -g

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -o $@ -c $^ -I$(HEADER) $(INCLUDE)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re