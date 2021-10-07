# Some tests to check and return.

## Shell
Starting minishell inside of minishell

## Builtins
### echo
```
cmd_echo("");						==>	\n						ok
cmd_echo("pouet lol     ri");		==>	pouet lol ri\n			ok
cmd_echo("-");						==>	-\n						ok
cmd_echo("-n");						==>	[new prompt]			ok
cmd_echo("-n je suis le     roi");	==>	je suis le roi			ok
cmd_echo("$VAR");					==>	$VAR value
```
echo and VAR, if VAR=pouet
echo $VAR	==> print pouet
echo "$VAR"	==> print pouet
echo '$VAR'	==> print $VAR

### cd
```
cmd_cd("tests/no_perm", env);		==>	cd: tests/no_perm/: Permission denied		ok
cmd_cd("no_exist", en);				==>	cd: no_exist: No such file or directory		ok
cmd_cd("../", env);					==>	go ../										ok
cmd_cd("~", env);					==>	go /User/me									
cmd_cd("/", env);					==>	go /										ok
cmd_cd("$VAR", env);				==>	go $VAR value
cmd_cd("-", env);					==>	go $OLDPWD									ok
cmd_cd("- ", env);					==>	go $OLDPWD									ok
cmd_cd("-     sdf", env);			==>	go $OLDPWD (ignore rest)					ok
cmd_cd("-ldf", env);				==> cd: -l: invalid option						cd: -ldf: No such file or directory
```


### export
```
cmd_export(ms_envp, "POUET=lol err BIP=Boup PWD=/ POUET=bip");	==> print error with "err", others are add to ms_env, pouet is add then update
cmd_export(ms_envp, "");								==> ??
```

### unset
Test to remove the first, the last
```
cmd_unset(&ms_envp, "ROBERT");	==> Remove ROBERT if exist, otherwise do nothing
cmd_unset(&ms_envp, NULL);		==> Do nothing
cmd_unset(&ms_envp, ms_split("TERM_PROGRAM PLOP POUET @sdf PWD ROBERT TERM"));	==> Remove if exist, otherwise do nothing, non valid print error
```