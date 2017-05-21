/*
** execute.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Mar  9 14:13:51 2017 romain pillot
** Last update Sun May 21 17:40:24 2017 romain pillot
*/

#include "environment.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"
#include "util.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include "builtin.h"

static void   (* const builtins[]) (t_shell *shell, char **args) =
{
  &cd_alt, &setenv_alt, &unsetenv_alt, &exit_alt, &echo_alt, &env_alt
};

static void	catch_child_exit(t_shell *shell, int pid, t_cmd *cmd)
{
  char		*error;
  int		wstatus;
  int		status;
  int		hold;

  check_close(cmd);
  if (cmd->writter_channels[0] != CHANNEL_NONE)
    return ;
  while (waitpid(pid, &wstatus, 0) != pid);  
  if (WIFEXITED(wstatus))
    shell->status = WEXITSTATUS(wstatus) ? EXIT_FAILURE : EXIT_SUCCESS;
  if (WIFSIGNALED(wstatus))
    {
      status = 1;
      if ((error = wstatus == 8 && (status = 136) ? FLOATING_STR_X :
	   wstatus == 11 && (status = 139) ? SEGFAULT_STR_X :
	   wstatus == (status = 136) ? FLOATING_STR :
	   wstatus == (status = 139) ? SEGFAULT_STR : NULL))
	display(error);
      shell->status = status;
    }
}

bool	execute(t_shell *shell, char *path, t_cmd *cmd, bool builtin)
{
  pid_t		pid;

  if (!check_pipe(cmd))
    return (false);
  if (builtin && !cmd->callback)
    {
      check_close(cmd);
      builtins[get_cmd_index(cmd->args[0])](shell, cmd->args);
    }
  else if ((pid = fork()) == -1)
    perror(cmd->args[0]);
  else if (pid == CHILD_PROCESS)
    execute_child(shell, path, cmd, builtin);
  else
    catch_child_exit(shell, pid, cmd);
  return (true);
}

static int	try_exec_access(char *path, char **denied, bool freepath)
{
  struct stat	rights;
  int		right;

  if (access(path, F_OK) != -1 && access(path, X_OK) != -1)
    if (!stat(path, &rights) && rights.st_mode && (rights.st_mode & S_IEXEC))
      right = ACCESS;
    else
      {
        safe_free(*denied);
	*denied = path;
	right = DENIED;
      }
  else
    right = NOT_FOUND;
  if (right == NOT_FOUND && freepath)
    safe_free(path);
  return (right);
}

static int	check_paths(t_shell *shell, t_cmd *cmd, char **denied, bool *success)
{
  char		*str;
  char		**hold;
  char		**paths;
  int		right;

  paths = (hold = get_paths(shell->env));
  right = NOT_FOUND;
  while (paths && (str = *paths++))
    {
      str = concatstr(str, "/", false);
      str = concatstr(str, cmd->args[0], true);
      if ((right = try_exec_access(str, denied, true)) == ACCESS)
	{
	  *success = execute(shell, str, cmd, false);
	  free(str);
	  break;
	}
    }
  safe_freesub(hold, true);
  return (right);
}

bool            search_cmd(t_shell *shell, t_cmd *cmd)
{
  char          *str;
  char		*denied;
  int		right;
  bool		has_slash;
  bool		success;

  denied = NULL;
  success = false;
  if ((has_slash = count_char(cmd->args[0], '/') > 0) &&
      (right = try_exec_access(cmd->args[0], &denied, false)) == ACCESS)
    success = execute(shell, cmd->args[0], cmd, false);
  else if (!has_slash)
    right = check_paths(shell, cmd, &denied, &success);
  display(right == ACCESS ? NULL : denied ? denied : cmd->args[0]);
  display(right == ACCESS ? NULL : denied ? DENIED_STR : NFOUND_STR);
  if (right == NOT_FOUND)
    shell->status = EXIT_FAILURE;
  safe_free(denied);
  return (success);
}
