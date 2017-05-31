/*
** test.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed May 31 09:29:54 2017 romain pillot
** Last update Wed May 31 09:30:29 2017 romain pillot
*/

#include "minishell.h"
#include "util.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "builtin.h"

int     get_cmd_index(char *str)
{
  return (equalstr(str, "cd") ? CD :
	  equalstr(str, "setenv") ? SETENV :
	  equalstr(str, "unsetenv") ? UNSETENV :
	  equalstr(str, "echo") ? ECHO :
	  equalstr(str, "env") ? ENV :
	  equalstr(str, "exit") ? EXIT : SEARCH_CMD);
}
