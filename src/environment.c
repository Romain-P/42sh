/*
** environment.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 11:44:53 2017 romain pillot
** Last update Tue May 16 14:40:22 2017 romain pillot
*/

#include "environment.h"
#include "util.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int	count_similar_keys(char **a, char **b)
{
  char		*str;
  char		*tofree;
  char		**split;
  int		i;

  i = 0;
  while (a && (str = *a++))
    {
      split = splitstr((tofree = strdupl(str)), '=');
      if (tab_start_withstr(b, split[0]))
	i++;
      free(tofree);
      free(split);
    }
  return (i);
}

char    **copy_env(char **env, char **overwrite)
{
  char  *str;
  char  *tofree;
  char  **split;
  char  *var;
  int   added;
  char  **new;
  char  **hold;

  added = tab_length(env) - count_similar_keys(env, overwrite);
  if (!(hold = (new  = malloc(sizeof(char *) * (tab_length(env) + added + 1)))))
    return (NULL);
  while(env && (str = *env++))
    {
      split = splitstr((tofree = strdupl(str)), '=');
      *new++ = strdupl(((var = tab_start_withstr(overwrite, split[0])) &&
			overwrite++ ? var : str));
      free(tofree);
      free(split);
    }
  while (overwrite && *overwrite)
    *new++ = strdupl(*overwrite++);
  *new = 0;
  return (hold);
}

void	set_value(char **env, char *key, char *val)
{
  char	*value;
  char	**tofree;
  bool	found;

  found = false;
  while (env && !found && (value = *env++))
    {
      tofree = splitstr(strdup(value), '=');
      if ((found = equalstr(tofree[0], key)))
	{
	  tofree[1] = val;
	  env[-1] = joinstr(tofree, "=");
	}
      safe_freesub(tofree, true);
    }
}

char	*get_value(char **env, char *key)
{
  char	*value;
  char	**tofree;
  char	*found;

  found = NULL;
  while (!found && env && (value = *env++))
    {
      tofree = splitstr(strdup(value), '=');
      if (equalstr(tofree[0], key))
	found = strdup(tofree[1]);
      safe_freesub(tofree, true);
    }
  return (found);
}

char    **get_paths(char **env)
{
  char  *str;

  while (env && (str = *env++))
    if (start_withstr(str, "PATH"))
      return (splitstr(strdupl(str + 5), ':'));
  return (NULL);
}
