/*
** util.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/util
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Mar  9 15:55:33 2017 romain pillot
** Last update Thu Mar  9 16:21:08 2017 romain pillot
*/

#include "util.h"
#include <stdlib.h>

bool	safe_free(void *ptr)
{
  bool	done;

  if ((done = ptr != NULL))
    free(ptr);
  return (done);
}

bool	safe_freesub(char **ptr, bool free_sub)
{
  bool	done;

  if ((done = ptr != NULL))
    {
      if (free_sub && (done = *ptr != NULL))
	free(*ptr);
      free(ptr);
    }
  return (done);
}
