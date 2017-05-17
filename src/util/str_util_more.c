/*
** str_util_more.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/util
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 10:25:12 2017 romain pillot
** Last update Wed May 17 11:44:47 2017 romain pillot
*/

#include <stdbool.h>
#include "util.h"
#include <stdlib.h>
#include <string.h>

bool	start_withstr(char *str, char *charset)
{
  if (!str || !charset)
    return (false);
  while (*charset)
    if (*str++ != *charset++)
      return (false);
  return (true);
}

char	*strdupl(char *str)
{
  char	*new;
  char	*hold;

  if (!(hold = (new = malloc(sizeof(char) * (str_length(str) + 1)))))
    return (NULL);
  while (*str)
    *new++ = *str++;
  *new = 0;
  return (hold);
}

char	*concatstr(char *a, char *b, bool free_a)
{
  char	*concat;
  char	*hold;
  char	*hold_a;

  if (!(hold = (concat = malloc(sizeof(char) * (str_length(a) +
						str_length(b) + 1)))))
    return (NULL);
  hold_a = a;
  while (a && *a)
    *concat++ = *a++;
  while (b && *b)
    *concat++ = *b++;
  *concat = 0;
  if (free_a && hold_a)
    free(hold_a);
  return (hold);
}

char	*joinstr(char **tab, char *joiner)
{
  char	*str;
  char	*value;

  str = NULL;
  while (tab && (value = *tab++))
    if (str)
      str = concatstr(concatstr(str, joiner, true), value, true);
    else
      str = strdup(value);
  return (str);
}

char    *copystr(unsigned char *from, int lenf,
		 unsigned char *to, int index)
{
  int   len;
  int   i;

  i = 0;
  if (!from || !to || index < 0)
    return (NULL);
  while (i < lenf)
    to[index++] = from[i++];
  to[index] = 0;
  return (to);
}
