/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:41:12 by maria-ol          #+#    #+#             */
/*   Updated: 2025/08/27 22:17:36 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief Safely deallocates memory and sets pointer to NULL.
 *
 * This function frees the memory pointed to by the pointer stored at 
 * 'address_ptr' and then sets that pointer to NULL to prevent dangling 
 * pointer issues. If either 'address_ptr' or the pointer it points to 
 * is NULL, the function does nothing.
 *
 * @param address_ptr Pointer to a pointer that will be freed and set to NULL.
 * @return None.
 */
static void	ft_memdel(void **address_ptr)
{
	if (address_ptr && *address_ptr)
	{
		free(*address_ptr);
		*address_ptr = NULL;
	}
}

/**
 * @brief Reads from file descriptor and concatenates data to existing scraps.
 *
 * Continuously reads data from the file descriptor in chunks of BUFFER_SIZE
 * until a newline character is found or end of file is reached. Each read
 * chunk is concatenated to the existing 'scraps' string. The function handles
 * memory management by freeing the old 'scraps' after each concatenation.
 *
 * @param scraps The existing string to which new data will be concatenated.
 * @param buffer Temporary buffer used for reading data from the file descriptor.
 * @param fd The file descriptor to read from.
 * @return The updated string containing all concatenated data, or NULL on error.
 */
static void	read_and_concat_to_scraps(char **scraps, char *buffer, int fd)
{
	char		*temp;
	ssize_t		bytes_read;

	bytes_read = 1;
	while (!(ft_strchr(*scraps, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_memdel((void **)scraps);
			return ;
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*scraps, buffer);
		if (!temp)
		{
			ft_memdel((void **)scraps);
			return ;
		}
		ft_memdel((void **)scraps);
		*scraps = temp;
	}
}

/**
 * @brief Extracts a single line from the scraps string.
 *
 * Searches for the first newline character in 'scraps' and creates a substring
 * from the beginning up to and including the newline. If no newline is found,
 * the entire 'scraps' string is duplicated. This function is used to extract
 * the current line that should be returned by get_next_line.
 *
 * @param scraps The string containing buffered data from file reads.
 * @return A new string containing one line (with newline if present), 
 *         or NULL if allocation fails.
 */
static char	*extract_line(char *scraps)
{
	char	*line;
	char	*new_line;
	size_t	len;

	if (!scraps)
		return (NULL);
	line = ft_strchr(scraps, '\n');
	if (line)
	{
		len = (line - scraps) + 1;
		new_line = ft_substr(scraps, 0, len);
	}
	else
		new_line = ft_strdup(scraps);
	return (new_line);
}

/**
 * @brief Extracts remaining data after the current line.
 *
 * After extracting a line, this function creates a new string containing
 * all data that comes after the first newline character in 'scraps'. 
 * The original 'scraps' memory is freed. If no newline is found, it means
 * all data was consumed and NULL is returned.
 *
 * @param scraps The string containing buffered data.
 * @return A new string with leftover data for subsequent calls, 
 *         or NULL if no data remains or allocation fails.
 */
static void	extract_leftovers(char **scraps)
{
	char	*leftovers;
	char	*pos_new_line;
	size_t	i_start;

	if (!scraps || !*scraps)
		return ;
	pos_new_line = ft_strchr(*scraps, '\n');
	if (!pos_new_line)
	{
		ft_memdel((void **)scraps);
		return ;
	}
	else
	{
		i_start = (pos_new_line - *scraps) + 1;
		leftovers = ft_substr(*scraps, i_start, ft_strlen(*scraps) - i_start);
		ft_memdel((void **)scraps);
	}
	*scraps = leftovers;
}

/**
 * @brief Reads and returns the next line from a file descriptor.
 *
 * This function reads from a file descriptor one line at a time, where a line
 * is defined as a sequence of characters ending with '\n' or EOF. It uses a
 * static variable to maintain state between calls, allowing it to handle files
 * larger than the buffer size. Memory is automatically managed and cleaned up.
 *
 * @param fd The file descriptor to read from.
 * @return A string containing the next line (including '\n' if present), 
 *         or NULL when EOF is reached or an error occurs.
 */
char	*get_next_line(int fd)
{
	static char	*scraps[FD_MAX] = {NULL};
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
	{
		if (scraps[fd])
			ft_memdel((void **)&scraps[fd]);
		return (NULL);
	}
	if (!scraps[fd])
		scraps[fd] = ft_strdup("");
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_and_concat_to_scraps(&scraps[fd], buffer, fd);
	ft_memdel((void **)&buffer);
	if (!scraps[fd] || scraps[fd][0] == '\0')
	{
		ft_memdel((void **)&scraps[fd]);
		return (NULL);
	}
	line = extract_line(scraps[fd]);
	extract_leftovers(&scraps[fd]);
	return (line);
}
