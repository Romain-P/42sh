/*
** setenv.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:36:55 2017 romain pillot
** Last update Tue May 16 10:54:57 2017 romain pillot
*/

#include "builtin.h"
#include "environment.h"
#include <stdio.h>
#include "util.h"
#include <stdlib.h>

static	bool valid_key(char *key)
{
  int	i;

  i = -1;
  while (key[++i])
    if (key[i] != '_' && !(key[i] >= 'a' && key[i] <= 'z') &&
	!(key[i] >= 'A' && key[i] <= 'Z'))
      {
	if (!i || (i > 0 && !(key[i] > '0' && key[i] < '9')))
	  {
	    display(!i ? "setenv: Variable name must begin with a letter\n" :
		    "setenv: Variable name must contain alphanumeric characters.\n");
	    return (false);
	  }
      }
  return (true);
}

void	setenv_alt(t_shell *shell, char **args)
{
  char	**hold;
  char	*overwrite[2];

  if (!args[1])
    {
      display_environment(shell->env, '\n');
      return ;
    }
  else if (!valid_key(args[1]))
    return ;
  overwrite[0] = concatstr(concatstr(args[1], "=", false), args[2], true);
  overwrite[1] = 0;
  shell->env = copy_env((hold = shell->env), overwrite);
  free_tab(hold);
  free(*overwrite);
}
