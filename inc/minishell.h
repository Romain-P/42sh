/*
** main.h for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:15:51 2016 romain pillot
** Last update Tue May 16 16:10:00 2017 romain pillot
*/

#ifndef MINISHELL_H_
# define MINISHELL_H_

# include "stdbool.h"

# define CHILD_PROCESS	(0)

# define CMDS		(6)
# define CD		(0)
# define SETENV		(1)
# define UNSETENV	(2)
# define ENV		(3)
# define EXIT		(4)
# define SEARCH_CMD	(5)

# define NOT_FOUND	(0)
# define DENIED		(-1)
# define ACCESS		(1)
# define DENIED_STR	(": Permission denied.\n")
# define NFOUND_STR	(": Command not found.\n")
# define SEGFAULT_STR	("Segmentation fault (core dumped)\n")

typedef struct		s_shell
{
  bool			isatty;
  char			***aliases;
  char			**env;
  int			status;
  void			(*exit)(struct s_shell *shell, int status, char *message);
}			t_shell;

void			launch(t_shell *shell, int file);

int			get_cmd_index(char *cmd);

void			apply_command(t_shell *shell, char *cmd_line);

void			search_cmd(t_shell *shell, char **args);

#endif /** !MINISHELL_H_ **/
