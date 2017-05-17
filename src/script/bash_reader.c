/*
** bash_reader.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 16 16:00:37 2017 romain pillot
** Last update Wed May 17 12:55:38 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include "util.h"
#include <string.h>
#include <stdlib.h>

static bool	initialize(t_shell *shell)
{
  if (!(shell->scripts = malloc(sizeof(t_scripts))))
    return (false);
  shell->scripts->bashrc = NULL;
  return (shell->scripts->aliases = list_create());
}

void	init_scripts(t_shell *shell)
{
  int	fd;
  char	**split;

  if (!initialize(shell) || (fd = open_filename("~/.bashrc")) == -1)
    return ;
  if (shell->scripts->bashrc = file_content(fd))
    {
      split = splitstr(strdup(shell->scripts->bashrc), '\n');
      load_aliases(shell, split);
      load_exports(shell, split);
      safe_freesub(split, true);
    }
  close(fd);
}
