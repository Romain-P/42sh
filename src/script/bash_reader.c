/*
** bash_reader.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed May 31 09:29:22 2017 romain pillot
** Last update Wed May 31 09:29:23 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include "environment.h"

static bool	initialize(t_shell *shell)
{
  if (!(shell->scripts = malloc(sizeof(t_scripts))) ||
      !(shell->scripts->aliases = list_create()))
    return (false);
  shell->scripts->bashrc = NULL;
  return (true);
}

void	init_scripts(t_shell *shell)
{
  int	fd;
  char	**split;
  char	*path;

  path = concatstr(concatstr(get_value(shell->env, "HOME"), "/", true),
		   SHRC, true);
  if (initialize(shell) && (fd = open_filename(path)) != -1)
    {
      if ((shell->scripts->bashrc = file_content(fd)))
	{
	  split = splitstr(strdup(shell->scripts->bashrc), '\n');
	  load_aliases(shell, split);
	  load_exports(shell, split);
	  safe_freesub(split, true);
	}
      close(fd);
    }
  safe_free(path);
}
