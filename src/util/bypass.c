/*
** bypass.c for  in /home/romain.pillot/projects/shell/src/util
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed May 17 16:09:46 2017 romain pillot
** Last update Wed May 31 09:26:34 2017 romain pillot
*/

#include "util.h"
#include <unistd.h>
#include <stdlib.h>

char	*balloc(int size)
{
  char	*mem;

  mem = NULL;
  if (!(mem = malloc(sizeof(char) * (size + 1))))
    return (mem);
  return (mem);
}

char	*reballoc(char *old, int size)
{
  char	*mem;

  mem = NULL;
  if (!(mem = realloc(old, sizeof(char) * (size + 1))))
    return (mem);
  return (mem);
}
