#include "minishell.h"

/* create the loop that will run minishell */

int main(void)
{
    int status;
    char *line;

    status = 1;
    while (status)
    {
        line = readline("user@root > ");
        cmd_exit(line);
        add_history(line);
    }
    return (1);
}