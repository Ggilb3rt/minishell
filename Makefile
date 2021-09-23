#Hello

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIB = -lreadline
	INCLUDE = -I
else
	LIB = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
	INCLUDE = -I /Users/$(USER)/.brew/opt/readline/include
endif

include sources.mk
NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra -g
HEADER = includes
SRC = sources
OBJ = objects
SRCS = $(addprefix $(SRC)/, $(SOURCES))
OBJS = $(addprefix $(OBJ)/, $(SOURCES:.c=.o))
RM = rm -rf

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $@
	cd objects && mkdir -p parsing
	cd objects && mkdir -p commands
	cd objects && mkdir -p history
	cd objects && mkdir -p utils
	cd objects && mkdir -p exec
	cd objects && mkdir -p pipes
	cd objects && mkdir -p redirs

$(OBJS): | $(OBJ)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(FLAGS) -o $@ -c $^ -I$(HEADER) $(INCLUDE)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re