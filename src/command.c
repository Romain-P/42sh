/*
** command.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri May 19 10:17:27 2017 romain pillot
** Last update Sun May 21 17:34:14 2017 romain pillot
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

static t_cmd	*private_build(t_cmd *cmd)
{
  t_cmd		*hold;

  hold = cmd;
  while (cmd)
    {
      if (!str_length(cmd->cmd_line))
	{
	  if (cmd->type_in != CHEVRON_NONE || cmd->type_out != CHEVRON_NONE ||
	      cmd->reader_channels[0] != CHANNEL_NONE ||
	      cmd->writter_channels[0] != CHANNEL_NONE)
	    display(NULL_CMD_STR);
	  free_command(hold, true);
	  return (NULL);
	}
      cmd = cmd->callback;
    }
  return (hold);
}

t_cmd		*build_commands(t_shell *shell, char *cmds_line)
{
  t_cmd		*cmd;

  if (!parse_separators(trimstr(cmds_line, ' '), (cmd = create_command(NULL))))
    display(NULL_CMD_STR);
  else if (!parse_redirections(cmd))
    display(MISSING_STR);
  else
    return (private_build(cmd));
  free_command(cmd, true);
  shell->status = EXIT_FAILURE;
  return (NULL);
}

void	free_command(t_cmd *cmd, bool full)
{
  t_cmd	*hold;

  hold = cmd;
  if (!full)
    {
      safe_free(cmd->cmd_line);
      safe_freesub(cmd->args, true);
      safe_free(cmd->redirection_out);
      safe_free(cmd->redirection_in);
      safe_free(cmd);
    }
  else
    while ((cmd = hold))
      {
	hold = hold->callback;
	safe_free(cmd->cmd_line);
	safe_freesub(cmd->args, true);
	safe_free(cmd->redirection_out);
	safe_free(cmd->redirection_in);
	safe_free(cmd);
      }
}
