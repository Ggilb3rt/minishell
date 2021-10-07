cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell sources/utils/utils_1.c sources/history/history.c includes/history.h includes/parsing.h sources/parsing/parsing_main.c includes/utils.h includes/builtins.h sources/builtins/builtin_pwd.c sources/builtins/builtin_echo.c sources/builtins/builtin_cd.c sources/builtins/builtin_export.c sources/builtins/builtin_unset.c sources/builtins/builtin_env.c sources/builtins/builtin_exit.c sources/exec/exec.c includes/exec.h sources/pipes/pipes.c includes/pipes.h includes/flux.h sources/utils/utils_2.c sources/utils/utils_4.c sources/utils/utils_3.c sources/flux/flux_redir_input.c sources/flux/flux_redir_output.c sources/flux/flux_append.c sources/flux/flux_heredoc.c sources/flux/flux_pipe.c sources/env/env.c includes/env.h sources/debug/debug.c sources/parsing/parsing_elem.c sources/parsing/parsing_cmd.c sources/parsing/parsing_node.c)
