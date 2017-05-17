/*
** export.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed May 17 11:27:29 2017 romain pillot
** Last update Wed May 17 17:47:18 2017 romain pillot
*/

#include "minishell.h"
#include "util.h"
#include "environment.h"

void	load_exports(t_shell *shell, char **file_content)
{
  char		*str;
  int		i;
  char		*buffer[2];
  char		**hold;

  buffer[1] = 0;
  i = -1;
  while (str = file_content[++i])
    {
      if (start_withstr(str, "export"))
	{
	  buffer[0] = str + 7;
	  hold = shell->env;
	  shell->env = copy_env(hold, buffer);
	  free_tab(hold);
	}
    }
}
