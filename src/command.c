/*
** command.c for  in /home/romain.pillot/projects/shell/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri May 19 10:17:27 2017 romain pillot
** Last update Fri May 19 14:40:30 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>

static t_cmd	*create_command(char *args)
{
  t_cmd		*cmd;

  if (!(cmd = malloc(sizeof(t_cmd))))
    return (NULL);
  cmd->args = args;
  cmd->channels[CHANNEL_READ] = -1;
  cmd->channels[CHANNEL_WRITE] = -1;
  cmd->channel = CHANNEL_NONE;
  cmd->callback = NULL;
  cmd->callback_type = CALLBACK_NONE;
  cmd->redirection_in = NULL;
  cmd->redirection_out = NULL;
  return (cmd);
}

t_cmd   **parse_commands(char *cmd)
{
  char  **a;
  char  **b;
  char  **c;

  a = splitstr((strdup(cmd), ";"));
  
  safe_freesub(a, true);
}
