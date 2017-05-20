/*
** redirector_parser.c for  in /home/romain.pillot/projects/shell/src/parser
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sat May 20 13:23:01 2017 romain pillot
** Last update Sat May 20 16:59:55 2017 romain pillot
*/

#include "minishell.h"
#include "util.h"

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

int	parse_file(char *str, char **redirection, int op_size)
{
  int	i;
  int	j;

  i = str[op_size] == ' ' || str[op_size] == '\t' ? op_size + 1 : op_size;
  while (str[i] && str[i] != ' ' && str[i] != '\t' && ++i);
  *redirection = copystr(str, i - 1, 0, 0);
  j = 0;
  while (j < i)
    str[j++] = ' ';
  return (!i ? i : i - 1);
}

bool		parse_redirections(t_cmd *cmd)
{
  int		i;
  int		idx;
  t_triple_int	values;
  char		**redirection;
  int		*type;

  while (cmd)
    {
      i = -1;
      while (cmd->cmd_line[++i])
	{
	  if ((values = parse_chevron(cmd->cmd_line + i)).first != CHEVRON_NONE)
	    {
	      redirection = values.first == CHEVRON_INPUT ?
		&cmd->redirection_in : &cmd->redirection_out;
	      type = values.first == CHEVRON_INPUT ?
		&cmd->type_in : &cmd->type_out;
	      *type = values.second;
	      i += parse_file(cmd->cmd_line + i, redirection, values.third);
	      i += values.third;
	    }
	}
      trimstr(cmd->cmd_line, ' ');
      cmd = cmd->callback;
    }
}
