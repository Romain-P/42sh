/*
** file.c for  in /home/romain.pillot/projects/shell/src/script
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed May 17 11:40:02 2017 romain pillot
** Last update Wed May 17 12:38:43 2017 romain pillot
*/

#include "util.h"
#include "script.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char                    *file_content(int file)
{
  unsigned char         *content;
  unsigned char         buffer[1024 + 1];
  int                   bytes;
  int                   len;

  content = NULL;
  len = 0;
  while ((bytes = read(file, buffer, 1024)) && bytes != -1)
    {
      buffer[bytes] = 0;
      len += bytes;
            content = !content ?
	      copystr(buffer, bytes, malloc(sizeof(char) * (len + 1)), 0) :
	      copystr(buffer, bytes, realloc(content,
					     sizeof(char) * (len + 1)), len - bytes);
    }
  if (bytes == -1)
    {
      safe_free(content);
      return (NULL);
    }
  return (content);
}

int             open_filename(char *file_name)
{
  return (open(file_name, O_RDONLY));
}
