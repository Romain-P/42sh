/*
** redirector_parser.c for  in /home/romain.pillot/projects/shell/src/parser
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sat May 20 13:23:01 2017 romain pillot
** Last update Sun May 21 21:39:44 2017 romain pillot
*/

#include "minishell.h"
#include "util.h"
#include <string.h>

static t_triple_int	parse_chevron(char *str)
{
  return (start_withstr(str, SEPARATOR_CHEVRON_OUTPUT_DOUBLE) ?
	  (t_triple_int) {CHEVRON_OUTPUT, CHEVRON_DOUBLE,
	      str_length(SEPARATOR_CHEVRON_OUTPUT_DOUBLE)} :
	  start_withstr(str, SEPARATOR_CHEVRON_INPUT_DOUBLE) ?
	  (t_triple_int) {CHEVRON_INPUT, CHEVRON_DOUBLE,
	      str_length(SEPARATOR_CHEVRON_INPUT_DOUBLE)} :
	  start_withstr(str, SEPARATOR_CHEVRON_INPUT) ?
	  (t_triple_int) {CHEVRON_INPUT, CHEVRON_SIMPLE,
	      str_length(SEPARATOR_CHEVRON_INPUT)} :
	  start_withstr(str, SEPARATOR_CHEVRON_OUTPUT) ?
	  (t_triple_int) {CHEVRON_OUTPUT, CHEVRON_SIMPLE,
	      str_length(SEPARATOR_CHEVRON_OUTPUT)} :
	  (t_triple_int) {CHEVRON_NONE, CHEVRON_NONE, 0});
}

static bool	beside_chevron(char next)
{
  char		buffer[3];

  buffer[0] = next;
  buffer[1] = next;
  buffer[2] = 0;
  return (parse_chevron(buffer).first != CHEVRON_NONE);
}

static int	parse_file(char *str, char **redirection, int op_size)
{
  int		i;
  int		j;
  int		k;

  i = (k =str[op_size] == ' ' || str[op_size] == '\t' ? op_size + 1 : op_size);
  if (!str[i] || beside_chevron(str[i]))
    return (-1);
  while (str[i] && str[i] != ' ' && str[i] != '\t' && ++i);
  *redirection = copystr(str + k, i - 1, 0, 0);
  j = 0;
  while (j < i)
    str[j++] = ' ';
  return (i - op_size - 1);
}

static bool	apply_redirection_properties(t_triple_int *values, t_cmd *cmd, int i)
{
  char          **redirection;
  int           *type;

  redirection = values->first == CHEVRON_INPUT ?
    &cmd->redirection_in : &cmd->redirection_out;
  type = values->first == CHEVRON_INPUT ?
    &cmd->type_in : &cmd->type_out;
  *type = values->second;
  values->first = parse_file(cmd->cmd_line + i, redirection, values->third);
  return (values->first != -1);
}

bool		parse_redirections(t_cmd *cmd)
{
  int		i;
  t_triple_int	values;

  while (cmd && (i = -1))
    {
      while (cmd && cmd->cmd_line && cmd->cmd_line[++i])
	if ((values = parse_chevron(cmd->cmd_line + i)).first != CHEVRON_NONE)
	  {
	    if (!apply_redirection_properties(&values, cmd, i))
	      return (false);
	    i += values.first;
	    i += values.third;
	  }
      cmd->args = cmd->cmd_line ? splitstr(strdup(trimstr(cmd->cmd_line, ' ')), ' ') :
	NULL;
      cmd = cmd->callback;
    }
  return (true);
}
