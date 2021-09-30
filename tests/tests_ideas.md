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
cmd_echo("$VAR");					==>	$VAR value
```
echo and VAR, if VAR=pouet
echo $VAR	==> print pouet
echo "$VAR"	==> print pouet
echo '$VAR'	==> print $VAR

### cd
```
cmd_cd("tests/no_perm", env);		==>	cd: tests/no_perm/: Permission denied
cmd_cd("no_exist", en);				==>	cd: no_exist: No such file or directory
cmd_cd("../", env);					==>	go ../
cmd_cd("~", env);					==>	go /User/me
cmd_cd("/", env);					==>	go /
cmd_cd("$VAR", env);				==>	go $VAR value
cmd_cd("-", env);					==>	go $OLDPWD
cmd_cd("-     sdf", env);			==>	go $OLDPWD (ignore rest)
cmd_cd("-ldf", env);				==> cd: -l: invalid option
```