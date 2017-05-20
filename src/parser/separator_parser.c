/*
** separator_parser.c for  in /home/romain.pillot/projects/shell/src/parser
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sat May 20 13:17:08 2017 romain pillot
** Last update Sat May 20 21:15:15 2017 romain pillot
*/

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>

static t_double_int     parse_callback(char *str)
{
  return (start_withstr(str, SEPARATOR_ONSUCCESS) ?
	  (t_double_int) {CALLBACK_ONSUCCESS, str_length(SEPARATOR_ONSUCCESS)} :
	  start_withstr(str, SEPARATOR_ONFAILURE) ?
	  (t_double_int) {CALLBACK_ONFAILURE, str_length(SEPARATOR_ONFAILURE)} :
	  start_withstr(str, SEPARATOR_ALLCASES) ?
	  (t_double_int) {CALLBACK_ALLCASES, str_length(SEPARATOR_ALLCASES)} :
	  start_withstr(str, SEPARATOR_PIPE) ?
	  (t_double_int) {CALLBACK_PIPE, str_length(SEPARATOR_PIPE)} :
	  (t_double_int) {CALLBACK_NONE, 0});
}

static void     apply_callback_properties(t_cmd **cmd, int callback_type)
{
  t_cmd         *hold;

  hold = *cmd;
  hold->callback_type = callback_type;
  *cmd = (hold->callback = create_command(NULL));
  if (callback_type != CALLBACK_PIPE)
    return ;
  hold->channel = CHANNEL_WRITE;
  hold->callback->channel = CHANNEL_READ;
}

static bool	beside_separators(t_double_int values, char *cmds_line)
{
  char		str[3];
  char		next;

  next = cmds_line[values.second];
  str[0] = next;
  str[1] = next;
  str[2] = 0;
  return (parse_callback(str).first != CALLBACK_NONE);
}

bool		parse_separators(char *cmds_line, t_cmd *cmd)
{
  int           i;
  int           cmd_idx;
  t_double_int  values;
  bool          end;

  cmd_idx = 0;
  i = -1;
  while (cmds_line[++i])
    {
      if ((values = parse_callback(cmds_line + i)).first != CALLBACK_NONE ||
	  (end = !cmds_line[i + 1]))
	{
	  if (values.first && (!i || beside_separators(values, cmds_line + i) ||
			       !cmds_line[i + values.second]))
	    return (false);
	  cmd->cmd_line = copystr(cmds_line + cmd_idx, i - cmd_idx + end, 0, 0);
	}
      if (values.first != CALLBACK_NONE)
	{
	  apply_callback_properties(&cmd, values.first);
	  cmd_idx = (i += values.second);
	}
    }
  return (true);
}
