- fd leaks when exit | exit
- voir les valeurs de retour quand exit avec les signaux
- quand pas de path et que le shell trouve pas l'executable, bash affiche un message "no such file"
- probleme signaux dans heredoc (probablement du au remplacement des exit() par g_ret.quit)
- segfault ./minishell < /dev/urandom

**Comprends pas :**
	- leaks de temps en temps en faisant exit
		trouver a quel moment

**En cours :**
	- revoir messages erreur
		- pour execve (cmd not found and permission denied)						| OK
		- in file	(permission denied, return 1) 								| OK
		- out file	(permission denied, return 1)								| OK
		- heredoc

**Fait :**
	- "export name" ne doit pas ajouter ou changer la var (ok) mais n'affiche pas d'erreur non plus
	- exit et pipes
	- put builtins cd to the norme
	- command not found doit renvoyer code erreur de 127 (ici 2)				| OK
	- permission denied doit renvoyer code erreur de 126 (ici 13)				| OK
	- cd - double free aiiiiie													| OK
	- cd sans arguments est censé aller dans le home (attention au cas ou la variable HOME est pas set)
		cd sans arguments va dans home, ecrit message erreur si HOME pas set	| OK
	- "echo -nnn -nnnnn -nnnnn hey" devrait se comporter comme "echo -n hey"	| OK
	- dans bash, export sans argument trie les variables par ordre alphabetique	| OK
		pas forcement, ca depends de la distrib et de l'os
		Dans le man : "When no arguments are given, the results are unspecified."
	- builtins modifient la valeur de $?
		cd return 1 en cas d'erreur												| OK
		unset return 1 en cas d'erreur											| OK
		exit																	| OK
		export, return 1 en cas d'erreur										| OK
		env pas check (comme pas d'options devrait toujours return 0)			| OK
		pwd (comme env)															| OK
		echo je sais pas lui faire retourner une erreur (comme env)				| OK ?
