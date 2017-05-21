/*
** alias.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 16 16:12:23 2017 romain pillot
** Last update Sun May 21 21:35:18 2017 romain pillot
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
	  split = splitstr(strdup(str), '=');
	  alias = malloc(sizeof(t_alias));
	  alias->name = strdup(split[0] + 6);
	  length = str_length(split[1]);
	  split[1][length - 1] = 0;
	  alias->content = strdup(split[1] + 1);
	  list_add(shell->scripts->aliases, alias);
	  safe_freesub(split, true);
	}
    }
  alias = malloc(sizeof(t_alias));
  alias->name  = strdup("..");
  alias->content = strdup("cd ..");
  list_add(shell->scripts->aliases, alias);
}

static char	*replace(char **cmd, t_alias *alias, t_list *aliases)
{
  char		*line;
  char		*hold;
  char		*recurse;

  line = concatstr(concatstr(alias->content, " ", false),
		   (hold = joinstr(cmd + 1, " ")), true);
  if ((recurse = format_alias(line, aliases)) != line)
    {
      free(line);
      line = recurse;
    }
  free(hold);
  safe_freesub(cmd, true);
  return (line);
}

char		*format_alias(char *cmd, t_list *aliases)
{
  t_elem	*elem;
  t_alias	*found;
  char		**split;

  elem = aliases->first;
  found = NULL;
  split = splitstr(strdupl(cmd),  ' ');
  while (!found && elem)
    {
      if (!start_withstr(cmd, ((t_alias *) elem->get)->content) &&
	  equalstr(((t_alias *) elem->get)->name, split[0]))
	found = (t_alias *) elem->get;
      elem = elem->next;
    }
  if (!found)
    safe_freesub(split, true);
  return (found ? replace(split, found, aliases) : strdup(cmd));
}
