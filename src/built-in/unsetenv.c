/*
** unsetenv.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:37:57 2017 romain pillot
** Last update Fri May 19 14:37:40 2017 romain pillot
*/

#include <stdlib.h>
#include "builtin.h"
#include "util.h"

static  bool valid_key(char *key)
{
  int   i;

  i = -1;
  while (key[++i])
    if (key[i] != '_' && !(key[i] >= 'a' && key[i] <= 'z') &&
	!(key[i] >= 'A' && key[i] <= 'Z'))
      if (!i || (i > 0 && !(key[i] >= '0' && key[i] <= '9')))
	return (false);
  return (true);
}

void	unsetenv_alt(t_shell *shell, char **args)
{
  char	**env;
  char	*line;
  bool	refactoring;

  refactoring = false;
  if (!args[1])
    {
      display("unsetenv: Too few arguments.\n");
      shell->status = EXIT_FAILURE;
      return ;
    }
  env = shell->env;
  while ((line = *env++))
    {
      if (valid_key(args[1]) && start_withstr(line, args[1]))
	{
	  free(line);
	  refactoring = true;
	}
      if (refactoring)
	env[-1] = *env;
    }
  shell->status = EXIT_SUCCESS;
}
