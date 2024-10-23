/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:15:14 by eproust           #+#    #+#             */
/*   Updated: 2024/10/22 18:43:35 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	alloc_strings(char **stash, char **buffer)
{
	int	i;

	if (!*stash)
	{
		*stash = malloc(sizeof(char));
		if (!*stash)
			return (0);
		(*stash)[0] = '\0';
	}
	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buffer)
	{
		free(*stash);
		return (0);
	}
	i = 0;
	while (i <= BUFFER_SIZE)
		(*buffer)[i++] = '\0';
	return (1);
}

void	*free_strings(char **stash, char **buffer)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

/*
   static char	*get_line(char **stash, int bytes_read)
   {
   char	*line;
   char	*nl_ptr;
   char	*stash_tmp;

   line = NULL;
   nl_ptr = ft_strchr(*stash, '\n');
   if (nl_ptr)
   {
   line = ft_substr(*stash, 0, nl_ptr - *stash + 1);
   if (!line)
   return (free_ptr(stash));

//stash_tmp = ft_strdup(*stash);
stash_tmp = ft_substr(*stash, nl_ptr - *stash + 1, ft_strlen(nl_ptr));
if (!stash_tmp)
return (free_ptr(stash));
free_ptr(stash);
 *stash = stash_tmp;
 }
 else if (bytes_read == 0)
 {
 line = ft_substr(*stash, 0, ft_strlen(*stash));
 if (!line)
 return (free_ptr(stash));
 free_ptr(stash);
 }
 if (!line || !ft_strlen(line))
 return (NULL);
 return (line);
 }
 */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	int			bytes_read;
	char		*buffer;
	char		*nl_ptr;

	if (fd < 0 || BUFFER_SIZE <= 0 || !alloc_strings(&stash, &buffer))
		return (NULL);
	line = NULL;
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strrchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_strings(&stash, &buffer));
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (free_strings(&stash, &buffer));	
	}
	free(buffer); 
	nl_ptr = ft_strrchr(stash, '\n'); // use strrchr pour optimiser
	line = ft_substr(stash, 0, nl_ptr - stash + 1);
	stash = ft_strdup(nl_ptr + 1);
	//printf("(%s|%s|%s)", nl_ptr, line, stash);
	return (line);
}
