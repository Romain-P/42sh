/*
** exit.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:38:50 2017 romain pillot
** Last update Thu May 18 16:39:41 2017 Clement Gomis
*/

#include "builtin.h"
#include <stdlib.h>
#include "util.h"
#include <unistd.h>

char	format_escaped(char c)
{
  return (c == 'n' ? '\n' :
	  c == 't' ? '\t' :
	  c == 'a' ? '\a' :
	  c == 'b' ? '\b' :
	  c == 'e' ? '\e' :
	  c == 'f' ? '\f' :
	  c == 'r' ? '\r' :
	  c == 'v' ? '\v' : 0);
}

void	echo_alt(t_shell *shell, char **args)
{
  char	*str;
  int	i;
  char	format;
  bool	display_return;

  display_return = !equalstr(args[1], "-n");
  str = joinstr(args + (display_return ? 1 : 2), " ");
  i = -1;
  while (str[++i])
    {
      if (str[i] == '\\')
	{
	  if ((format = format_escaped(str[i + 1])) && ++i)
	    display_char(format);
	  else
	    write(STDOUT_FILENO, str + i, 2);
	}
      else
	display_char(str[i]);
    }
  if (display_return)
    display_char('\n');
  safe_free(str);
}
