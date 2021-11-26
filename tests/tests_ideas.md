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

## Parsing
```
cat < Makefile | grep c | wc < test_file	==>	print wc < text_file result
ls -la > out | grep source > out2			==> out gets ls -la return and out2 is create butls empty
`ls -la | grep source | cat -e > out | ls`	==> return ls -la | grep source | cat -e in out then print ls
```
!Send results in pipes while there is no outfile
```
`ls > out1 > out2 > out3`						==> créé trois fichiers mais seul out3 contient le resultat
`cat < sources.mk < Makefile`					==> utilise Makefile comme entrée de cat (error si sources.mk n'existe pas)
`grep CC > out < Makefile`					==> working well, out gets the result of grep CC with Makefile infile
```
Utilise toujour le dernier fichier, créé les autres si nécessaire.

```
cat > out -e sources.mk						==> cree et ecrit le contenu de sources.mk dans out, l'option -e fonctionne
```


Le killer
```
``cat << eof < README.md > toto >> yolo | > poto < Makefile grep s>> moto << eof2``
```
## "" and ''
```
echo '$USER' "$USER '$USER'"			==> '$USER' ggilbert 'ggilbert'
```

## No way !
In bash if you unset PATH, nothing will works after. Think about checking path before run builtins functions ?


## Subject
```
cat | cat | ls		==> must print ls then you can "cat" two times
```

## Find on discord
fd leaks
```
ulimit -n                                  # nombre de fd dispo max (pour expliquer le principe de fd leaks a l'evalué)
ls /proc/self/fd                           # affiche le nombre fd utilisés par le process enfant il faut donc repeter cette commande plusieurs fois lors de la correction pour verifier les fd leaks
ls | ls | ls /proc/self/fd                 # regarder le nombre de fd
ls | ls | ls | ls | ls | ls /proc/self/fd  # le nombre de fd doit etre le meme que la ligne d'avant!
# essayer aussi avec des redirections!
```
Trivialites
```
#lancer minishell comme ceci puis faire des bails
env -i ./minishell

# redirections:
>test                        # doit creer test
>>test                       # doit creer test
<test                        # doit essayer d'ouvrir test
cat <a <b >c >d              # input b output d
# pipes
ls | cat                     # affiche ls
cat | ls                     # doit afficher ls puis doit exit apres un \n
#   les redirections doivent etre faites APRES les pipes, (donc sont prioritaires par ecrasement)
cat a | < b cat | cat > c | cat # b doit etre copié dans c, rien ne doit etre ecrit dans stdout
# execution
./non_executable             # permission denied exit code 126
./directory
non_executable               # avec non_executable dans un dossier du path, permission denied
cat < directory
```

Parsing
```
export A="s -la" #puis faire
l$A #doit executer un ls -la (donc que le split se fait apres le remplacement de var d'env)

export A=p #puis faire
export B=w #puis faire
$A"$B"d  #doit executer un pwd, puis faire
"$A"'$B'd #ne doit pas faire de pwd car les var d'env ne sont pas remplacee dans les simple quote

echo "ls -la <a | grep x > b" #doit afficher "ls -la <a | grep x > b"
echo ok "" ok #doit avoir deux espaces car "" est un argument vide mais est un argument
echo ok "" "" "" "" "" "" "" "" "" ok #pour mieux voir ce qui est avant

export OK="ok                   ok" #puis faire
echo $OK #doit afficher "ok ok" (un seul espace entre les deux

# si il y a le ; qui est fait
unset A #pour etre sur que la variable d'environnement existe pas puis faire la suite sur une autre ligne de commande
export A=ok; echo $A  #doit afficher un ok
```