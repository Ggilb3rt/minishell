cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c sources/utils/utils_1.c sources/history/history.c includes/history.h includes/parsing.h sources/parsing/parsing.c includes/utils.h includes/commands.h sources/commands/cmd_pwd.c sources/commands/cmd_echo.c sources/commands/cmd_cd.c sources/commands/cmd_export.c sources/commands/cmd_unset.c sources/commands/cmd_env.c sources/commands/cmd_exit.c)
