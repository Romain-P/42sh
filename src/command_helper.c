/*
** command_helper.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 21 15:15:00 2017 romain pillot
** Last update Tue May 30 21:35:52 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "builtin.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void   (* const builtins[]) (t_shell *shell, char **args) =
{
  &cd_alt, &setenv_alt, &unsetenv_alt, &exit_alt, &echo_alt, &env_alt
};

void    check_close(t_cmd *cmd, bool redirection)
{
  if (cmd->reader_channels[0] != CHANNEL_NONE)
    {
      close(cmd->reader_channels[CHANNEL_READ]);
      close(cmd->reader_channels[CHANNEL_WRITE]);
    }
  if (!redirection)
    return ;
  if (cmd->fd_in)
    fclose(cmd->fd_in);
  if(cmd->fd_out)
    fclose(cmd->fd_out);
}

bool    check_dup(t_cmd *cmd)
{
  if (cmd->reader_channels[0] != CHANNEL_NONE &&
      dup2(cmd->reader_channels[CHANNEL_READ], STDIN_FILENO) == -1)
    {
      perror(cmd->args[0]);
      return (false);
    }
  if (cmd->writter_channels[0] != CHANNEL_NONE &&
      dup2(cmd->writter_channels[CHANNEL_WRITE], STDOUT_FILENO) == -1)
    {
      perror(cmd->args[0]);
      return (false);
    }
  return (true);
}

bool    check_pipe(t_cmd *cmd)
{
  if (cmd->writter_channels[0] != CHANNEL_NONE)
    {
      if (pipe(cmd->writter_channels) == -1)
	{
	  perror(cmd->args[0]);
	  return (false);
	}
      cmd->callback->reader_channels[CHANNEL_READ] =
	cmd->writter_channels[CHANNEL_READ];
      cmd->callback->reader_channels[CHANNEL_WRITE] =
	cmd->writter_channels[CHANNEL_WRITE];
    }
  return (true);
}

bool	check_redirection(t_cmd *cmd, bool builtin, int *in, int *out)
{
  FILE	*fd;

  if (cmd->redirection_out)
    {
      if (!(fd = fopen(cmd->redirection_out,
		       cmd->type_out == CHEVRON_DOUBLE ? "a" : "w")))
	{
	  perror(cmd->args[0]);
	  return (false);
	}
      *out = builtin ? dup(STDOUT_FILENO) : -1;
      dup2(fileno((cmd->fd_out = fd)), STDOUT_FILENO);
    }
  if (cmd->redirection_in && cmd->type_in == CHEVRON_SIMPLE)
    {
      if (!(fd = fopen(cmd->redirection_in, "r")))
	{
	  perror(cmd->args[0]);
	  return (false);
	}
      *in = builtin ? dup(STDIN_FILENO) : -1;
      dup2(fileno((cmd->fd_in = fd)), STDIN_FILENO);
    }
  return (true);
}

bool    execute_child(t_shell *shell, char *path, t_cmd *cmd, bool builtin)
{
  char	*error;
  int	stdin;
  int	stdout;

  stdin = CHANNEL_NONE;
  stdout = CHANNEL_NONE;
  if (!check_dup(cmd) || !check_redirection(cmd, false, &stdin, &stdout))
    return (false);
  check_close(cmd, false);
  if (!builtin && execve(path, cmd->args, shell->env) == -1)
    {
      if (start_withstr(INVALID_STR, (error = strerror(errno))))
	error = INVALID_STR;
      printf("%s: %s.\n", cmd->args[0], error);
    }
  else
    builtins[get_cmd_index(cmd->args[0])](shell, cmd->args);
  _exit(builtin ? shell->status : EXIT_FAILURE);
  return (true);
}
