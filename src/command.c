/*
** command.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri May 19 10:17:27 2017 romain pillot
** Last update Sun May 21 12:25:33 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>
#include <stdio.h>

t_cmd		*create_command(char *cmd_line)
{
  t_cmd		*cmd;

  if (!(cmd = malloc(sizeof(t_cmd))))
    return (NULL);
  cmd->cmd_line = cmd_line;
  cmd->args = NULL;
  cmd->reader_channels[CHANNEL_READ] = CHANNEL_NONE;
  cmd->reader_channels[CHANNEL_WRITE] = CHANNEL_NONE;
  cmd->writter_channels[CHANNEL_READ] = CHANNEL_NONE;
  cmd->writter_channels[CHANNEL_WRITE] = CHANNEL_NONE;
  cmd->callback = NULL;
  cmd->callback_type = CALLBACK_NONE;
  cmd->redirection_in = NULL;
  cmd->type_in = CHEVRON_NONE;
  cmd->redirection_out = NULL;
  cmd->type_out = CHEVRON_NONE;
  return (cmd);
}

t_cmd		*build_commands(t_shell *shell, char *cmds_line)
{
  t_cmd		*cmd;
  t_cmd		*hold;

  if (!parse_separators(trimstr(cmds_line, ' '), (cmd = create_command(NULL))))
    display(NULL_CMD_STR);
  else if (!parse_redirections((hold = cmd)))
    display(MISSING_STR);
  else
    {
      while (cmd)
	{
	  if (!str_length(cmd->cmd_line))
	    {
	      display(NULL_CMD_STR);
	      return (NULL);
	    }
	  cmd = cmd->callback;
	}
      return (hold);
    }
  shell->status = EXIT_FAILURE;
  return (NULL);
}

void	check_close(t_cmd *cmd)
{
  if (cmd->reader_channels[0] != CHANNEL_NONE)
    close(cmd->reader_channels[CHANNEL_READ]);
  if (cmd->writter_channels[0] != CHANNEL_NONE)
    close(cmd->writter_channels[CHANNEL_WRITE]);
}

bool	check_dup(t_cmd *cmd)
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

bool	check_pipe(t_cmd *cmd)
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
