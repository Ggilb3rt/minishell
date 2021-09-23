//
// Created by Antoine LANGLOIS on 23/09/2021.
//

# include "pipes.h"

/* external functions that we may use :
 * - int pipe(int pipefd[2]) : creates a pipe, a unidirectional data channel that can be used for interprocess
 * communication. The array 'pipefd' is used to return two file descriptors referring to the ends of the pipe.
 * 'pipefd[0]' refers to the read end of the pipe. 'pipefd[1]' refers to the write end of the pipe. Data written
 * to the write end of the pipe is buffered by the kernel until it is read from the read en of the pipe.
 */

/*
 * - int isatty(int fd) : tests whether 'fd' is an open file descriptor referring to a terminal.
 * returns 1 if 'fd' is an open file descriptor referring to a terminal, otherwise 0.
 */