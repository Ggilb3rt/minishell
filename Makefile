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
FLAGS = -Wall -Werror -Wextra -g
HEADER = includes
include sources.mk
SRC = sources
OBJ = objects
SOURCES =
SRCS = $(addprefix $(SRC)/, $(SOURCES))
OBJS = $(addprefix $(OBJ)/, $(SOURCES:.c=.o))

all: $(NAME)

$OBJ:
	mkdir -p $@

$(OBJS): | $OBJ

$(OBJ)/%.o: $(SRC)/%.c | $OBJ
	$(CC) $(FLAGS) -o $@ -c $^ -I$(HEADER) $(INCLUDE)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re