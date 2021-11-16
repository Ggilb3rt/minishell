# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

int main(void)
{
	int a = open("./out", O_CREAT | O_WRONLY, 0666);
	int b = open("./out1", O_CREAT | O_WRONLY, 0666);

	printf("%d %d\n", a, b);
	close(a);

	a = open("./out", O_CREAT | O_WRONLY | O_APPEND, 0666);
	b = open("./out", O_CREAT | O_WRONLY | O_APPEND, 0666);
	printf("%d %d\n", a, b);
}
