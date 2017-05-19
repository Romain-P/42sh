/*
** execute.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Mar  9 14:13:51 2017 romain pillot
** Last update Fri May 19 08:41:04 2017 romain pillot
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

static void	catch_child_exit(t_shell *shell, int pid)
{
  char		*error;
  int		wstatus;
  int		status;

  while (waitpid(pid, &wstatus, 0) != pid);
  if (WIFEXITED(wstatus))
    shell->status = WEXITSTATUS(wstatus);
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

static void	execute(t_shell *shell, char *path, char **args)
{
  pid_t		pid;
  char		*error;

  if ((pid = fork()) == -1)
    perror("fork");
  else if (pid == CHILD_PROCESS)
    {
      if (execve(path, args, shell->env) == -1)
	{
	  if (start_withstr(INVALID_STR, (error = strerror(errno))))
	    error = INVALID_STR;
	  printf("%s: %s\n", *args, error);
	  shell->exit(shell, EXIT_FAILURE, NULL);
	}
    }
  else
    catch_child_exit(shell, pid);
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

static int	check_paths(t_shell *shell, char **args, char **denied)
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
      str = concatstr(str, *args, true);
      if ((right = try_exec_access(str, denied, true)) == ACCESS)
	{
	  execute(shell, str, args);
	  free(str);
	  break;
	}
    }
  safe_freesub(hold, true);
  return (right);
}

void            search_cmd(t_shell *shell, char **args)
{
  char          *str;
  char		*denied;
  int		right;
  bool		has_slash;

  denied = NULL;
  if ((has_slash = count_char(*args, '/') > 0) &&
      (right = try_exec_access(*args, &denied, false)) == ACCESS)
    execute(shell, *args, args);
  else if (!has_slash)
    right = check_paths(shell, args, &denied);
  display(right == ACCESS ? NULL : denied ? denied : args[0]);
  display(right == ACCESS ? NULL : denied ? DENIED_STR : NFOUND_STR);
  safe_free(denied);
}
