/*
** env.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
**
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
**
** Started on  Wed Mar  8 13:35:17 2017 romain pillot
** Last update Fri May 19 14:36:23 2017 romain pillot
*/

#include "environment.h"
#include "util.h"
#include "builtin.h"
#include <stdlib.h>
#include <string.h>

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

static void    unbind(char **env, char *key)
{
  char  *line;
  bool  refactoring;

  while ((line = *env++))
    {
      if (valid_key(key) && start_withstr(line, key))
	{
	  free(line);
	  refactoring = true;
	}
      if (refactoring)
	env[-1] = *env;
    }
}

static int	apply_options(char ***addr, char **args)
{
  int		i;
  char		**env;
  char		**tofree;

  i = 0;
  env  = *addr;
  while (args[i + 1] && ++i)
    {
      if (start_withstr(args[i], "-i") ||
	   start_withstr(args[i], "--ignore_environment"))
	*addr = NULL;
      else if (start_withstr(args[i], "-0") || start_withstr(args[i], "--null"))
	display_environment(env, '\0');
      else if (start_withstr(args[i], "-u"))
	unbind(env, args[++i]);
      else if (start_withstr(args[i], "--unset"))
	{
	  tofree = splitstr((strdup(args[i])), '=');
	  unbind(env, tofree[1]);
	  safe_freesub(tofree, true);
	}
      else if (!start_withstr(args[i], "-"))
	break;
    }
  return (i);
}

void	env_alt(t_shell *shell, char **args)
{
  char	**env;
  char	**cpy;
  char	**hold;
  char	*tofree;
  int	index;

  cpy = shell->env;
  env = (hold = copy_env(cpy, NULL));
  index = apply_options(&env, args);
  if (!index)
    display_environment(shell->env, '\n');
  else if (!start_withstr(args[index], "-"))
    {
      shell->env = env;
      tofree = joinstr(args + index, " ");
      if (tofree)
	apply_command(shell, tofree);
      safe_free(tofree);
      shell->env = cpy;
    }
  shell->status = EXIT_SUCCESS;
  free_tab(hold);
}
