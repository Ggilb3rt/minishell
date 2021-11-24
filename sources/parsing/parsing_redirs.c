//
// Created by alangloi on 11/24/21.
//

#include "minishell.h"

static void redir_less(t_split *split, t_command *cmd)
{
	int i;

	i = 0;
	printf("yo\n");
	split->i++;
	del_spaces(split);
	cmd->in_file = malloc(sizeof(char) * (ret_val(split) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		if (ft_isalnum(split->str[split->i]))
		{
			cmd->in_file[i] = split->str[split->i];
			split->i++;
			i++;
		}
	}
	cmd->token_in = LESS;
	cmd->token_out = 0;
	cmd->in_file[i] = '\0';
}

static void redir_great(t_split *split, t_command *cmd)
{
	int i;

	i = 0;
	split->i++;
	del_spaces(split);
	cmd->out_file = malloc(sizeof(char) * (ret_val(split) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		if (ft_isalnum(split->str[split->i]))
		{
			cmd->out_file[i] = split->str[split->i];
			split->i++;
			i++;
		}
	}
	cmd->token_in = 0;
	cmd->token_out = GREAT;
	cmd->out_file[i] = '\0';
}

static void redir_dgreat(t_split *split, t_command *cmd)
{
	int i;

	i = 0;
	split->i += 2;
	del_spaces(split);
	cmd->out_file = malloc(sizeof(char) * (ret_val(split) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		if (ft_isalnum(split->str[split->i]))
		{
			cmd->out_file[i] = split->str[split->i];
			split->i++;
			i++;
		}
	}
	cmd->token_in = 0;
	cmd->token_out = DGREAT;
	cmd->out_file[i] = '\0';
}

static void redir_dless(t_split *split, t_command *cmd)
{
	int i;

	i = 0;
	split->i += 2;
	del_spaces(split);
	cmd->end = malloc(sizeof(char) * (ret_val(split) + 1));
	while (split->str[split->i] && split->str[split->i] != ' ')
	{
		if (ft_isalnum(split->str[split->i]))
		{
			cmd->end[i] = split->str[split->i];
			split->i++;
			i++;
		}
	}
	cmd->token_in = DLESS;
	cmd->token_out = 0;
	cmd->end[i] = '\0';
	g_ret.ret = EHERE;
}

void	redirection(t_split *split, t_command *cmd)
{
	if (split->str[split->i] == '<' && split->str[split->i + 1] != '<')
		redir_less(split, cmd);
	else if (split->str[split->i] == '>' && split->str[split->i + 1] != '>')
		redir_great(split, cmd);
	else if (split->str[split->i] == '>' && split->str[split->i + 1] == '>')
		redir_dgreat(split, cmd);
	else if (split->str[split->i] == '<' && split->str[split->i + 1] == '<')
		redir_dless(split, cmd);
}