# Some tests to check and return.

## Shell
Starting minishell inside of minishell

## Builtins
### echo
```
cmd_echo("");						==>	\n
cmd_echo("pouet lol     ri");		==>	pouet lol ri\n
cmd_echo("-");						==>	-\n
cmd_echo("-n");						==>	[new prompt]
cmd_echo("-n je suis le     roi");	==>	je suis le roi
```