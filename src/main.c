/*
** main.c for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:14:29 2016 romain pillot
** Last update Wed May 17 14:44:46 2017 romain pillot
*/

#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include <stdio.h>
#include <fcntl.h>
#include "environment.h"

static void	exit_shell(t_shell *shell, int status, char *msg)
{
  if (msg)
    display(msg);
  shell->status = status;
}

static int	open_file(const char *file_name, t_shell *shell)
{
  int		file;

  if ((file = open(file_name, O_RDONLY)) == -1)
    {
      perror(file_name);
      shell->status = EXIT_FAILURE;
    }
  return (file);
}

static void	free_all(t_shell *shell)
{
  t_elem	*elem;
  t_elem	*hold;

  free_tab(shell->env);
  free(shell->scripts->bashrc);
  elem = shell->scripts->aliases->first;
  while (elem)
    {
      free(((t_alias *) elem->get)->name);
      free(((t_alias *) elem->get)->content);
      hold = elem->next;
      free(elem->get);
      free(elem);
      elem = hold;
    }
  free(shell->scripts->aliases);
  free(shell->scripts);
  free(shell->history->cd);
  free(shell->history);
  free(shell);
}

int		main(int ac, char **args, char **env)
{
  t_shell	*shell;
  int		status;
  int		file;

  if (!(shell = malloc(sizeof(t_shell))) ||
      !(shell->history = malloc(sizeof(t_history))))
    return (EXIT_FAILURE);
  shell->status = -1;
  shell->env = copy_env(env, NULL);
  shell->history->cd = get_value(shell->env, "PWD");
  init_scripts(shell);
  if ((file = ac > 1 ? open_file(args[1], shell) : 0) != -1)
    {
      shell->isatty = isatty(file);
      shell->exit = &exit_shell;
      launch(shell, file);
      if (ac > 1 && shell->status != EXIT_FAILURE)
	close(file);
    }
  status = shell->status;
  free_all(shell);
  return (status);
}
