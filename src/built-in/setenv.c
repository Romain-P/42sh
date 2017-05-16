/*
** setenv.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:36:55 2017 romain pillot
** Last update Tue May 16 09:48:26 2017 romain pillot
*/

#include "builtin.h"
#include "environment.h"
#include <stdio.h>
#include "util.h"
#include <stdlib.h>

static bool valid_key(char *key)
{
  if (*key != '_' &&
      !(*key >= 'a' && *key <= 'z') &&
      !(*key >= 'A' && *key <= 'Z'))
    {
      display("setenv: Variable name must begin with a letter\n");
      return (false);
    }
  return (true);
}

void	setenv_alt(t_shell *shell, char **args)
{
  char	**hold;
  char	*overwrite[2];

  if (!args[1])
    {
      display_environment(shell->env);
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
