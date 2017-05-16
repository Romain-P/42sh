/*
** display.c for  in /home/romain.pillot/projects/PSU_2016_navy/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue Feb  7 14:39:21 2017 romain pillot
** Last update Thu Mar  9 16:16:07 2017 romain pillot
*/

#include "util.h"
#include <unistd.h>

int	str_length(char *str)
{
  int		i;

  i = 0;
  while (str && str[i] && ++i);
  return (i);
}

void	display(char *str)
{
  if (str)
    write(1, str, str_length(str));
}

void	display_digit(int digit)
{
  char	c;

  c = digit + '0';
  write(1, &c, 1);
}
  
void	display_char(char c)
{
  write(1, &c, 1);
}
