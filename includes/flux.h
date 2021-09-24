//
// Created by Antoine LANGLOIS on 23/09/2021.
//

#ifndef MINISHELL_REDIRS_H
#define MINISHELL_REDIRS_H

# include "minishell.h"

/* theses functions will handle all the redirections and pipes functionnalities
 * - < should redirect input
 * - > should redirect output
 * - << read input from the current source until a line containing only the delimiter is seen. it doesn't need to update
 * history
 * - >> should redirect output with append mode
 * - | pipes the output of each command in the pipeline is connected via a pipe to the input of the next command.
 */

void flux_pipe(void);
void flux_redir_output(void);
void flux_redir_input(void);
void flux_heredoc(void);
void flux_append(void);

#endif //MINISHELL_REDIRS_H
