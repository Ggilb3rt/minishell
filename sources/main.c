#include "minishell.h"

/* create the loop that will run minishell
 */

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("user@root > ");
        if (!parse_line(line))
			break ;
    }
    return (1);
}