/*
** cd.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
**
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
**
** Started on  Wed Mar  8 13:39:17 2017 romain pillot
** Last update Wed May 17 14:48:48 2017 Christian Betta
*/

#include "environment.h"
#include "util.h"
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"

int	flag_cd(t_shell *shell, char **args)
{
  if (equalstr(args[1], "-L") == true && args[2] == NULL)
    return (1);
  else if (equalstr(args[1], "-P") == true && args[2] == NULL)
    return (1);
  else if (equalstr(args[1], "-e") == true && args[2] == NULL)
    return (1);
  else if (args[1] == NULL)
    return (1);
  else
    return (0);
}

int	chg_rep(char **args)
{
  if (equalstr(args[1], "-L") == true ||
      equalstr(args[1], "-P") == true ||
      equalstr(args[1], "-e") == true)
    return (2);
  else
    return (1);
}

void	cd_alt(t_shell *shell, char **args)
{
  char	*value;
  char	buffer[1024];
  int	i;

  i = chg_rep(args);
  if (args[1] == NULL || (flag_cd(shell, args) == 1))
    {
      chdir((value = get_value(shell->env, "HOME")));
      free(value);
    }
  else if (chdir(args[i]) != 0)
    {
      display(args[i]);
      display(": No such file or directory.\n");
    }
  getcwd(buffer, 1024);
  set_value(shell->env, "PWD", buffer);
}
