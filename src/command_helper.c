/*
** command_helper.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 21 15:15:00 2017 romain pillot
** Last update Sun May 21 17:39:44 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "builtin.h"

static void   (* const builtins[]) (t_shell *shell, char **args) =
{
  &cd_alt, &setenv_alt, &unsetenv_alt, &exit_alt, &echo_alt, &env_alt
};

void    check_close(t_cmd *cmd)
{
  if (cmd->reader_channels[0] != CHANNEL_NONE)
    {
      close(cmd->reader_channels[CHANNEL_READ]);
      close(cmd->reader_channels[CHANNEL_WRITE]);
    }
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

void    execute_child(t_shell *shell, char *path, t_cmd *cmd, bool builtin)
{
  char	*error;

  check_dup(cmd);
  check_close(cmd);
  if (!builtin && execve(path, cmd->args, shell->env) == -1)
    {
      if (start_withstr(INVALID_STR, (error = strerror(errno))))
	error = INVALID_STR;
      printf("%s: %s.\n", cmd->args[0], error);
    }
  else
    builtins[get_cmd_index(cmd->args[0])](shell, cmd->args);
  _exit(builtin ? shell->status : EXIT_FAILURE);
}
