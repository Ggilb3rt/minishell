#Hello

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
<<<<<<< HEAD
	LIB = -lreadline
=======
	LIB = -lreadline -L/usr/include
>>>>>>> 285ca71b335f08004ebff8cce12dff413d92a5e2
	INCLUDE = -I/lib/x86_64-linux-gnu/readline
else
	LIB = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
	INCLUDE = -I /Users/$(USER)/.brew/opt/readline/include

	#LIB = -lreadline -L/usr/local/opt/readline/lib
	#INCLUDE = -I/usr/local/opt/readline/include
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
	cd objects && mkdir -p utils
	cd objects && mkdir -p exec
	cd objects && mkdir -p env
	cd objects && mkdir -p heredoc
	cd objects && mkdir -p debug
	cd objects && mkdir -p libft

$(OBJS): | $(OBJ)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB)
	@printf "Ready to go !\n"
	#make leak_test
	#./$(NAME)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@printf "Création des objets en cours : $@ ...\n"
	@$(CC) $(FLAGS) -o $@ -c $^ -I$(HEADER) $(INCLUDE)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

leaks_test:
	valgrind --leak-check=full --track-fds=yes ./$(NAME)

.PHONY: all fclean clean re letest