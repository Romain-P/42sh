/*
** export.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed May 17 11:27:29 2017 romain pillot
** Last update Sun May 21 21:35:30 2017 romain pillot
*/

#include "minishell.h"
#include "util.h"
#include "environment.h"
#include <string.h>
#include <stdlib.h>

void	load_exports(t_shell *shell, char **file_content)
{
  char		*str;
  int		i;
  char		*buffer[2];
  char		**hold;
  char		**split;
  int		length;

  buffer[1] = 0;
  i = -1;
  while ((str = file_content[++i]))
    {
      if (start_withstr(str, "export"))
	{
	  split = splitstr(strdup(str), '=');
	  length = str_length(split[1]);
	  split[1][length - 1] = 0;
	  str = concatstr(concatstr(split[0], "=", false), split[1] + 1, true);
	  buffer[0] = str + 7;
	  hold = shell->env;
	  shell->env = copy_env(hold, buffer);
	  free_tab(hold);
	  free(str);
	  safe_freesub(split, true);
	}
    }
}
