/*
** exit.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:38:50 2017 romain pillot
** Last update Thu Mar  9 00:42:09 2017 romain pillot
*/

#include "builtin.h"
#include <stdlib.h>

void	exit_alt(t_shell *shell, char **args)
{
  shell->exit(shell, EXIT_SUCCESS, shell->isatty ? "exit\n" : NULL);
}
