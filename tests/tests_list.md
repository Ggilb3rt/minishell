echo -n -n -nnnn -nnnnm
cat /dev/random | head -n 1 | cat -e
**unset var1 # with undefined var1**
export "" et unset "" #revoir messages erreur
$
**not_cmd bonjour > salut**
**env puis export puis env # vars aren't sorted**
cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code
cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code
cat Makefile | grep pr | head -n 5 | hello (NA) # check status code
**cat < test # with non-existent test a**
**echo bonjour > $test # with test not defined**
ctrl-C . 130 sur bin(ex : sleep 10)&line vide
minishell # binary not in path without "./" before
**exit -10**
**exit +10**
exit 0 | exit 1
exit 1 | exit 0

-------------------------------------------------------------------

PARSING/EXPANSION
**echo \\\$PATH**
**echo \"\"\"**
**echo \'\'\'**
**echo $"PWD"** #leaks guillaume
`echo \\\$PATH`
echo \"\"\"
echo \'\'\'
**echo $"PWD"**
**echo $HO"ME"**

RM BACKSLASH :  
**echo \>\>**

AST :
**<coucou echo ca va** #LEAKSLEAKSLEAKS
**echo coucou >text ca va**
**echo "-n "hello      world""**

EXECUTION :
**echo -n -n One"argument"'lo'l; echo**

EN VRAC FUCK :
**echo $"HOME"**
**echo "$     a"**
**$HOME $HOME $HOME**
**echo elie \ elie**
**echo elie$USER$PWD/elie$USER$?/elie$USERelie/$USER**
echo 'tom'rrr' et "bonjour" et 'tom' "elie" et "elie 'elie' tom"" ; echo "elie'tom and me'" tom elie 	tom ; echo 'tom' elie
**echo elie \ \ \ \ \ \ \ \ \ \ \ elie \ elie**
**echo "elie'$USER'elie$USER"**
**echo "elie 'tom et elie' elie $USER/elie"**
**echo "elie ""**
**echo |**
echo \ #LEAKSLEAKSLEAKS
>
=========================
- ls ;; ls
     ; ls ; ls
     **cat <<<<< bar**
     **cat << << bar**
     echo -nnnnnnnnnnnnnnnnnnnnn FOO
     echo -n -n -n -n bar
     echo "$ $ $ $ $SHELL----------$LOL.......$123TEST" #LEAKSLEAKSLEAKS
     cd ../../../..; pwd; echo $PWD; echo $OLDPWD
     export HELLO\WORLD
     export A==a; echo $A; export A=a=a=a=a=a; echo $A
     echo >> FILE foo
     echo >> FILE1 foo > FILE2
     `< main.c cat <redir.c < Makefile`
     **ec""ho bonjour**
     echo "\\"
     echo a\ \ \ \ \ \ \ b
     echo "a\ \ b c" '$SHELL'" (print erreur pas de gestion de multilignes)
     top | grep root
     **ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|
     ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|
     ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|
     ls|ls**
     <main.c cat <redir.c >file1 <Makefile >file2 >>file3 ; >f1 echo >>f2 coucou ca >f3 va >f4 et toi #PRINT TROP DE TRUCS
     **echo $PWD/file**
     - $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD      
     cd ..; pwd; echo $PWD; echo $OLDPWD
     echo $PWD; echo $OLDPWD; cd ../..; pwd; echo $PWD; echo $OLDPWD                                                    
     echo $PWD; echo $OLDPWD; cd ../../..; pwd; echo $PWD; echo $OLDPWD                                                 
     echo $PWD; echo $OLDPWD; cd ../../../..; pwd; echo $PWD; echo $OLDPWD                                              
     echo $PWD; echo $OLDPWD; cd ../../../../..; pwd; echo $PWD; echo $OLDPWD                                           
     echo $PWD; echo $OLDPWD; cd ../../../../../..; pwd; echo $PWD; echo $OLDPWD
     ~~cd /; pwd; echo $PWD; echo $OLDPWD~~                                     
     ~~cd /.; pwd; echo $PWD; echo $OLDPWD~~
     ~~cd /././././; pwd; echo $PWD; echo $OLDPWD~~
     ~~cd //; pwd; echo $PWD; echo $OLDPWD~~
     cd //////////////////////////////////////////////////////; pwd; echo $PWD; echo $OLDPWD
     **cd //home;**
     cd $HOME/Bureau
     unset HOME; cd
     export HOME= ; cd
     cd Documents .. #too many arguements
     cd -   #double free aiaiaiaie
     ./a.out (sur fichier non executable retourne 126)
     **export $var=test**
     **export $var=test avec var unset**
     **export la même variable**
     **unset var (var 1 ne doit pas etre unset)**

------------------------------------------------------------------------

cd ~
**echo |**
**| echo**
**cat < >**
> a ls > b < Makefile
**> log echo coucou** #LEAKSLEAKSLEAKS
**echo ''**
**ecrire "nom_dun_fichier" puis ctrl-c ne marche pas**
**echo ""**
~~echo bonjour ; |~~
**echo bonjour | |**
**|**
~~echo bonjour |;~~
~~echo bonjour ; ls~~
~~echo bonjour > test\ 1~~
**cd $HOME/Documents**
~~echo "\s" & echo "\s"~~
**echo >**
**echo test > file test1**
**echo bonjour >>> test** #revoir message erreur
**echo bonjour > > out**
**echo 2 >> out1 > out2**
**echo 2 > out1 >> out2**
~~export var; export var=test~~
**file_name_in_current_dir**
~~cd ../../../../../.. ; pwd~~
~~ctrl-\ .131 sur bin~~
~~echo "bip | bip ; coyotte > < " "~~
**cat | cat | cat | ls # check outputs order**
**$bla # with bla not defined**
**export var ="cat Makefile | grep >"**
**export "test=ici"=coucou**
**c$var Makefile # with var=at**
**$LESS$VAR**
**/bin/echo bonjour**
**not_cmd**
**sleep 5 | exit**
**echo bonjour > $test w/ t**
**"exit retour a la ligne"**
**cat diufosgid # check exit code**
**exit # should return the last exit code value**
~~;~~
~~echo coucou | ;~~
~~echo "$HOME"~~
~~echo '$HOME'~~
~~export ; env # display is different for both commands~~
~~echo $HOME~~
**echo hudifg d | | hugdfihd**
**echo**
**echo simple**
**echo -n simple**
~~echo "\"~~
~~echo "\n \n \n"~~
~~echo "\n \n \\n"~~
~~echo ;;~~
~~echo hi";" hihi~~
~~echo hi " ; " hihi~~
**cd**
**cd .**
**cd /**
**cd no_file**
**cd a b c d**
**pwd a**
**pwd a b c d**
**export LOL=lala ROR=rara**
**unset LOL ROR**
**export "HI= hi"**
**export "HI =hi"**
**/bin/ls**
# write something the press ctrl+c
# write something then press ctrl+d
# write something then press ctrl+\
**echo $?**
**l^Ds**
**sort | ls # check output order**
**cat < <**
**cat > >**
**echo > a Hello World!**
**> a echo Hello World!**
**cat < Makefile | grep gcc > output**




-----------------------------
Problemes du sujet

**Doubles quotes**
echo "cat lol.c | cat > lol,c $"USER""
     nous => cat lol.c | cat > lol,c USER
     leaks => non, invalid read of size
     bash => cat lol.c | cat > lol,c $USER

