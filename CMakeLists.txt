cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c sources/utils/utils_1.c sources/history/history.c includes/history.h includes/parsing.h sources/parsing/parsing.c includes/utils.h includes/commands.h sources/commands/cmd_pwd.c sources/commands/cmd_echo.c sources/commands/cmd_cd.c sources/commands/cmd_export.c sources/commands/cmd_unset.c sources/commands/cmd_env.c sources/commands/cmd_exit.c sources/exec/exec.c includes/exec.h sources/pipes/pipes.c includes/pipes.h includes/flux.h sources/utils/utils_2.c sources/utils/utils_4.c sources/utils/utils_3.c sources/flux/flux_redir_input.c sources/flux/flux_redir_output.c sources/flux/flux_append.c sources/flux/flux_heredoc.c sources/flux/flux_pipe.c sources/env/env.c includes/env.h)
