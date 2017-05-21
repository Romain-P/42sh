/*
** shell.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri Mar  3 02:18:12 2017 romain pillot
** Last update Sun May 21 17:28:02 2017 romain pillot
*/

#include "minishell.h"
#include "util.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "builtin.h"

static bool	has_child;

static void	display_prompt()
{
  char		*sub;
  char		path[1024];

  sub = NULL;
  if (getcwd(path, 1024))
    {
      display(count_char(path, '/') > 2 ?
	      (sub = rev_substr(path, '/', 2)) : path);
      display("> ");
      if (sub)
	free(sub);
    }
  else
    perror("getcwd");
}

static void     exit_handle()
{
  display_char('\n');
  if (!has_child)
    display_prompt();
}

static t_cmd	*apply_callback(t_shell *shell, t_cmd *cmd)
{
  bool		successed;

  successed = !shell->status;
  return (cmd->callback_type == CALLBACK_ONSUCCESS ? successed ? cmd->callback : NULL :
	  cmd->callback_type == CALLBACK_ONFAILURE ? !successed ? cmd->callback : NULL :
	  cmd->callback);
}

void	build_and_exec(t_shell *shell, char *cmds_line)
{
  char		*hold;
  int		index;
  t_cmd		*cmd;
  t_cmd		*hold_cmd;

  has_child = true;
  cmd = build_commands(shell, cmds_line);
  while ((hold_cmd = cmd))
    {
      hold = cmd->cmd_line;
      cmd->cmd_line = format_alias(hold, shell->scripts->aliases);
      index = get_cmd_index(cmd->args[0]);
      if (index == SEARCH_CMD && !search_cmd(shell, cmd))
	{
	  free_command(cmd, false);
	  break;
	}
      else if (index != SEARCH_CMD)
	execute(shell, NULL, cmd, true);
      cmd = apply_callback(shell, cmd);
      free_command(hold_cmd, !cmd);
      free(hold);
    }
  free(cmds_line);
}

void		launch(t_shell *shell, int file)
{
  char		*cmds_line;
  t_cmd		*cmd;

  signal(SIGINT, &exit_handle);
  shell->running = true;
  shell->status = EXIT_SUCCESS;
  while (shell->running)
    {
      has_child = false;
      if (shell->isatty)
	display_prompt();
      if (!(cmds_line = scan_line(file)))
	shell->exit(shell, shell->status, shell->isatty ? "exit\n" : NULL);
      else
	build_and_exec(shell, cmds_line);
    }
}

int     get_cmd_index(char *str)
{
  return (equalstr(str, "cd") ? CD :
	  equalstr(str, "setenv") ? SETENV :
	  equalstr(str, "unsetenv") ? UNSETENV :
	  equalstr(str, "echo") ? ECHO :
	  equalstr(str, "env") ? ENV :
	  equalstr(str, "exit") ? EXIT : SEARCH_CMD);
}
