/*
** environment.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 11:44:53 2017 romain pillot
** Last update Tue May 16 11:56:05 2017 romain pillot
*/

#include "environment.h"
#include "util.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

void	display_environment(char **env, char end_line)
{
  char	*str;

  while (env && (str = *env++))
    printf("%s%c", str, end_line);
}

char    **get_paths(char **env)
{
  char  *str;

  while (env && (str = *env++))
    if (start_withstr(str, "PATH"))
      return (splitstr(strdupl(str + 5), ':'));
  return (NULL);
}
