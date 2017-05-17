/*
** alias.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 16 16:12:23 2017 romain pillot
** Last update Wed May 17 15:58:01 2017 Clement Gomis
*/

#include "minishell.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

void		load_aliases(t_shell *shell, char **file_content)
{
  int		i;
  char		*str;
  char		**split;
  t_alias	*alias;
  int		length;

  i = -1;
  while ((str = file_content[++i]))
    {
      if (start_withstr(str, "alias"))
	{
	  split = splitstr(str, '=');
	  alias = malloc(sizeof(t_alias));
	  alias->name = strdup(split[0] + 5);
	  length = str_length(split[1]);
	  split[1][length - 1] = 0;
	  alias->content = strdup(split[1] + 1);
	  list_add(shell->scripts->aliases, alias);
	  safe_freesub(split, true);
	}
    }  
		
}
