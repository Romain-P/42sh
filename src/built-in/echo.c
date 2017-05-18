/*
** exit.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:38:50 2017 romain pillot
** Last update Thu May 18 15:52:34 2017 romain pillot
*/

#include "builtin.h"
#include <stdlib.h>
#include "util.h"
#include <unistd.h>
#include <math.h>

static int	 convertOctalToDecimal(int octalNumber)
{
  int		decimalNumber;
  int		i;

  decimalNumber = (i = 0);
  while (octalNumber)
    {
      decimalNumber += (octalNumber % 10) * pow(8, i++);
      octalNumber /= 10;
    }
  return (decimalNumber);
}

static char	format_octal(char *str, int *i)
{
  int		j;
  int		octal;
  int		limit;

  limit = (octal = (j = 0));
  while (limit++ <= 3 && str[j] >= '0' && str[j] <= '9' && ++j && ++(*i))
    octal = octal * 10 + str[j - 1] - '0';
  return (octal ? convertOctalToDecimal(octal) : 0);
}

static char	format_escaped(char c)
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
	  if (str[i + 1] == '0')
	    display_char(format_octal(str + i + 1, &i));
	  else if ((format = format_escaped(str[i + 1])) && ++i)
	    display_char(format);
	  else
	    write(STDOUT_FILENO, str + i++, 2);
	}
      else
	display_char(str[i]);
    }
  if (display_return)
    display_char('\n');
  safe_free(str);
}
