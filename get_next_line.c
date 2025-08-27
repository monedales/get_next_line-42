/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:36:11 by maria-ol          #+#    #+#             */
/*   Updated: 2025/08/27 16:33:19 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// static void	gnl_cleanup()
// {
//     static char	*scraps = NULL;
//     if (scraps)
//     {
//         free(scraps);
//         scraps = NULL;
//     }
// }

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
	if (!temp)
		return (NULL);
	ft_memdel((void **)&scraps);
	scraps = temp;
	return (temp);
}

static char	*extract_line(char *scraps)
{
	char	*line;
	char	*new_line;
	size_t	len;

	line = ft_strchr(scraps, '\n');
	len = (line - scraps) + 1;
	if (line)
		new_line = ft_substr(scraps, 0, len);
	else
		new_line = ft_strdup(scraps);
	return (new_line);
}

static char	*extract_leftovers(char *scraps)
{
	char	*leftovers;
	char	*pos_new_line;
	size_t	i_start;

	pos_new_line = ft_strchr(scraps, '\n');
	if (!pos_new_line)
	{
		ft_memdel((void **)&scraps);
		return (NULL);
	}
	else
	{
		i_start = (pos_new_line - scraps) + 1;
		leftovers = ft_substr(scraps, i_start,
				ft_strlen(scraps) - i_start);
		ft_memdel((void **)&scraps);
	}
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*scraps = NULL;
	ssize_t		bytes_read;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (scraps)
			ft_memdel((void **)&scraps);
		return (NULL);
	}
	if (!scraps)
		scraps = ft_strdup("");
	bytes_read = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(scraps, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		scraps = concat_buffer(scraps, buffer);
	}
	if (!scraps || scraps[0] == '\0')
	{
		ft_memdel((void **)&buffer);
		ft_memdel((void **)&scraps);
		return (NULL);
	}
	line = extract_line(scraps);
	scraps = extract_leftovers(scraps);
	ft_memdel((void **)&buffer);
	return (line);
}

// #include "get_next_line.h"
// int	main(void)
// {
//     int		fd;
//     char	*line;

//     fd = open("text_gnl.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     gnl_cleanup(fd);

//     close(fd);
//     return (0);
// }
