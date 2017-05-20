/*
** command.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri May 19 10:17:27 2017 romain pillot
** Last update Sat May 20 21:21:42 2017 romain pillot
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
  cmd->channels[CHANNEL_READ] = -1;
  cmd->channels[CHANNEL_WRITE] = -1;
  cmd->channel = CHANNEL_NONE;
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

  if (!parse_separators(trimstr(cmds_line, ' '), (cmd = create_command(NULL))))
    display(NULL_CMD_STR);
  else if (!parse_redirections(cmd))
    display(MISSING_STR);
  else
    return (cmd);
  shell->status = EXIT_FAILURE;
  return (NULL);
}

