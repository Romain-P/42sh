/*
** environment.h for  in /home/romain.pillot/projects/PSU_2016_minishell1/include
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 20:29:17 2017 romain pillot
** Last update Tue May 16 08:27:54 2017 romain pillot
*/

#ifndef ENVIRONMENT_H_
# define ENVIRONMENT_H_

char	**copy_env(char **env, char **overwrite);

void	display_environment(char **env);

char	**get_paths(char **env);

#endif /* !ENVIRONMENT */
