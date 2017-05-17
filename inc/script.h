/*
** builtin.h for  in /home/romain.pillot/projects/PSU_2016_minishell1/include
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:41:13 2017 romain pillot
** Last update Wed May 17 15:22:00 2017 romain pillot
*/

#ifndef SCRIPT_H_
# define SCRIPT_H_

# include "minishell.h"

typedef struct s_shell	t_shell;

typedef struct          s_scripts
{
  char                  *bashrc;
  t_list                *aliases;
}                       t_scripts;

typedef struct	s_alias
{
  char		*name;
  char		*content;
}		t_alias;

void	init_scripts(t_shell *shell);

int     open_filename(char *file_name);

char    *file_content(int file_descriptor);

void	load_exports(t_shell *shell, char **file_content);

void	load_aliases(t_shell *shell, char **file_content);

char	*format_alias(char *cmd, t_list *aliases);

#endif /* !SCRIPT_H_ */
