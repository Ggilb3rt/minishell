#include "minishell.h"

int main(int argc, char **argv)
{
	int status;
	char *line;

	(void)argc;
	(void)argv;
	status = 1;
	while (status) {
		*line = readline("user@root >");
	}
	free(line);
}