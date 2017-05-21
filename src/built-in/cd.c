/*
** cd.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/built-in
**
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
**
** Started on  Wed Mar  8 13:39:17 2017 romain pillot
** Last update Sun May 21 16:42:32 2017 romain pillot
*/

#include "environment.h"
#include "util.h"
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"

static void	display_error(char *file)
{
  display(file);
  display(!access(file, F_OK) ? ": Not a directory.\n" :
	  ": No such file or directory.\n");
}

void	cd_alt(t_shell *shell, char **args)
{
  char	*value;
  char	*tmp_pwd;
  char	buffer[1024];

  tmp_pwd = shell->history->oldpwd;
  shell->status = EXIT_SUCCESS;
  shell->history->oldpwd = get_value(shell->env, "PWD");
  if (!args[1])
    {
      chdir((value = get_value(shell->env, "HOME")));
      free(value);
    }
  else if (equalstr(args[1], "-"))
    chdir(tmp_pwd);
  else if (chdir(args[1]))
    {
      display_error(args[1]);
      shell->status = EXIT_FAILURE;
    }
  safe_free(tmp_pwd);
  getcwd(buffer, 1024);
  set_value(shell->env, "PWD", buffer);
}
