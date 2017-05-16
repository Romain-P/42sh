/*
** builtin.h for  in /home/romain.pillot/projects/PSU_2016_minishell1/include
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:41:13 2017 romain pillot
** Last update Wed Mar  8 22:54:21 2017 romain pillot
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

# include "minishell.h"

void	cd_alt(t_shell *shell, char **args);

void	env_alt(t_shell *shell, char **args);

void	setenv_alt(t_shell *shell, char **args);

void	unsetenv_alt(t_shell *shell, char **args);

void	exit_alt(t_shell *shell, char **args);

#endif /* !BUILTIN_H_ */
