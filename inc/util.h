/*
** util.h for  in /home/romain.pillot/projects/PSU_2016_minishell1/include
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Mar  2 16:17:22 2017 romain pillot
** Last update Tue May 16 14:11:58 2017 romain pillot
*/

#ifndef UTIL_H_
# define UTIL_H_

# include "minishell.h"

char	*joinstr(char **tab, char *joiner);

char	*scan_line(const int file);

void    display(char *str);

void    display_char(char c);

void    display_digit(int i);

int	count_char(char *str, char c);

char	*rev_substr(char *str, char c, int index);

char	*trimstr(char *str, char c);

bool	equalstr(char *a, char *b);

char	**splitstr(char *str, char delimiter);

int	str_length(char *str);

bool	start_withstr(char *str, char *charset);

char	*tab_start_withstr(char **tab, char *charset);

int	tab_length(char **tab);

char	*strdupl(char *str);

void	free_tab(char **tab);

char	*concatstr(char *a, char *b, bool free_a);

bool	safe_freesub(char **ptr, bool free_sub);

bool	safe_free(void *ptr);

#endif /* !UTIL_H_ */
