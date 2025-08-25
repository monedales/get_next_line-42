/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:36:14 by maria-ol          #+#    #+#             */
/*   Updated: 2025/08/25 17:41:10 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>

# define BUFFER_SIZE 32

char	*get_next_line(int fd);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int chr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char *str);


#endif