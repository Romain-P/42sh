/*
** main.h for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:15:51 2016 romain pillot
** Last update Sun May 21 14:18:23 2017 romain pillot
*/

#ifndef MINISHELL_H_
# define MINISHELL_H_

# include "stdbool.h"
# include "list.h"
# include "script.h"

# define CHILD_PROCESS	(0)

# define CMDS		(6)
# define SEARCH_CMD	(-1)
# define CD		(0)
# define SETENV		(1)
# define UNSETENV	(2)
# define EXIT		(3)
# define ECHO		(4)

# define NOT_FOUND	(0)
# define DENIED		(-1)
# define ACCESS		(1)
# define DENIED_STR	(": Permission denied.\n")
# define NFOUND_STR	(": Command not found.\n")
# define INVALID_STR	("Exec format error. Binary file not executable")
# define SEGFAULT_STR	("Segmentation fault (core dumped)\n")
# define SEGFAULT_STR_X	("Segmentation fault\n")
# define FLOATING_STR	("Floating exception (core dumped)\n")
# define FLOATING_STR_X	("Floating exception\n")
# define NULL_CMD_STR	("Invalid null command.\n")
# define MISSING_STR	("Missing name for redirect\n")

# define CHANNEL_NONE	(-1)
# define CHANNEL_READ	(0)
# define CHANNEL_WRITE	(1)

# define SEPARATOR_ONSUCCESS			("&&")
# define SEPARATOR_ONFAILURE			("||")
# define SEPARATOR_ALLCASES			(";")
# define SEPARATOR_PIPE				("|")
# define SEPARATOR_CHEVRON_INPUT		("<")
# define SEPARATOR_CHEVRON_INPUT_DOUBLE		("<<")
# define SEPARATOR_CHEVRON_OUTPUT		(">")
# define SEPARATOR_CHEVRON_OUTPUT_DOUBLE	(">>")

# define CHEVRON_NONE			(-1)
# define CHEVRON_INPUT			(0)
# define CHEVRON_OUTPUT			(1)
# define CHEVRON_SIMPLE			(0)
# define CHEVRON_DOUBLE			(1)

# define CALLBACK_NONE		(0)
# define CALLBACK_ONSUCCESS	(1)
# define CALLBACK_ONFAILURE	(2)
# define CALLBACK_ALLCASES	(3)
# define CALLBACK_PIPE		(4)

typedef struct		s_cmd
{
  char			*cmd_line;
  char			**args;
  int			reader_channels[2];
  int			writter_channels[2];
  char			*redirection_out;
  int			type_out;
  char			*redirection_in;
  int			type_in;
  struct s_cmd		*callback;
  int			callback_type;
  int			previous_pid;
}			t_cmd;

typedef struct		s_history
{
  char			*oldpwd;
}			t_history;

typedef struct		s_shell
{
  bool			running;
  bool			isatty;
  char			**env;
  int			status;
  t_history		*history;
  t_scripts		*scripts;
  void			(*exit)(struct s_shell *shell, int status, char *message);
}			t_shell;

t_cmd			*create_command(char *args);

bool			check_pipe(t_cmd *cmd);

void			check_close(t_cmd *cmd);

bool			check_dup(t_cmd *cmd);

t_cmd			*build_commands(t_shell *shell, char *cmds_line);

bool			parse_redirections(t_cmd *cmd);

bool			parse_separators(char *cmds_line, t_cmd *cmd);

void			launch(t_shell *shell, int file);

int			get_cmd_index(char *cmd);

void			build_and_exec(t_shell *shell, char *cmds_line);

bool			search_cmd(t_shell *shell, t_cmd *cmd);

#endif /** !MINISHELL_H_ **/
