/*
** cd.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
**
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
**
** Started on  Wed Mar  8 13:39:17 2017 romain pillot
** Last update Tue May 16 16:22:09 2017 Christian Betta
*/

#include "util.h"
#include <stdlib.h>
#include "builtin.h"

void	cd_alt(t_shell *shell, char **args)
{
  int   a;
  char	*value;
  char	buffer[1024];

  if (args[1] == NULL)
    {
      chdir((value = get_value(shell->env, "HOME")));
      display(value);
      display("pute");
      free(value);
    }
  else
    {
      if (chdir(args[1]) == 0)
	a++;
      else
	{
	  display(args[1]);
	  display(": No such file or directory.\n");
	}
    }
  getcwd(buffer, 1024);
  set_value(shell->env, "PWD", buffer);
}
