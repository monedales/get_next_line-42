/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:36:11 by maria-ol          #+#    #+#             */
/*   Updated: 2025/08/26 18:30:04 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_memdel(void **adress_ptr)
{
	if (adress_ptr && *adress_ptr)
	{
		free(*adress_ptr);
		*adress_ptr = NULL;
	}
}

static char	*concat_buffer(char *scraps, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(scraps, buffer);
	ft_memdel(scraps);
	scraps = temp;
	return (temp);
}

static char	*extract_line(char **scraps)
{
	char	*line;
	char	*new_line;
	char	*leftovers;

	new_line = ft_strchr(*scraps, '\n');
	line = ft_substr(*scraps, 0, new_line - *scraps + 1);
	leftovers = ft_strdup(new_line + 1);
	ft_memdel(&(*scraps));
	*scraps = leftovers;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*scraps;
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!scraps)
		ft_strdup("");
	bytes_read = 1;
	while (!(ft_strchr(scraps, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		scraps = (void *)concat_buffer(scraps, buffer);
	}
	if (bytes_read < 0)
		ft_memdel(&scraps);
	if (scraps != 0)
		return (extract_line(&scraps));
	return (NULL);
}
