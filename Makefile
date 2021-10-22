#Hello

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIB = -lreadline
	INCLUDE =
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
	cd objects && mkdir -p builtins
	cd objects && mkdir -p history
	cd objects && mkdir -p utils
	cd objects && mkdir -p exec
	cd objects && mkdir -p env
	cd objects && mkdir -p flux
	cd objects && mkdir -p debug

$(OBJS): | $(OBJ)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB)
	printf "Ready to go !\n"
	#make letest

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@printf "Création des objets en cours : $@ ...\n"
	@$(CC) $(FLAGS) -o $@ -c $^ -I$(HEADER) $(INCLUDE)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

letest:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all fclean clean re letest