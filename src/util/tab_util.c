/*
** tab_util.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/util
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:58:37 2017 romain pillot
** Last update Wed Mar  8 21:17:55 2017 romain pillot
*/

#include "util.h"
#include <stdlib.h>

int	tab_length(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i] && ++i);
  return (i);
}

char	*tab_start_withstr(char **tab, char *charset)
{
  while (tab && *tab)
    if (start_withstr(*tab++, charset))
      return (*(tab - 1));
  return (NULL);
}

void	free_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i])
    free(tab[i]);
  if (tab)
    free(tab);
}
