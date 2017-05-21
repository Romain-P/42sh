/*
** command_helper.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 21 15:15:00 2017 romain pillot
** Last update Sun May 21 15:17:18 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>
#include <stdio.h>

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
