/*
** builtin.h for  in /home/romain.pillot/projects/PSU_2016_minishell1/include
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:41:13 2017 romain pillot
** Last update Wed May 17 11:28:49 2017 romain pillot
*/

#ifndef SCRIPT_H_
# define SCRIPT_H_

# include "minishell.h"

typedef struct	s_alias
{
  char		*name;
  char		*content;
}		t_alias;

void	load_exports(t_shell *shell);

void	load_aliases(t_shell *shell);

#endif /* !SCRIPT_H_ */
