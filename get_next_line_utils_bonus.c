/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:36:09 by maria-ol          #+#    #+#             */
/*   Updated: 2025/09/10 20:14:51 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
/**
 * @brief Computes the length of a null-terminated string.
 *
 * Counts the number of characters in the string until the null terminator.
 *
 * @param str The string whose length will be calculated.
 * @return The number of characters in the string, excluding the null terminator.
 */
size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * @brief Concatenate two string into a new one.
 *
 * Allocates memory (using malloc(3)) and returns a new string, 
 * which is the result of concatenating ’s1’ and ’s2’.
 *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string. NULL if the allocation fails.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	is1;
	size_t	is2;
	char	*nstr;

	if (!s1 || !s2)
		return (NULL);
	nstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!nstr)
		return (NULL);
	is1 = 0;
	while (s1[is1])
	{
		nstr[is1] = s1[is1];
		is1++;
	}
	is2 = 0;
	while (s2[is2])
	{
		nstr[is1 + is2] = s2[is2];
		is2++;
	}
	nstr[is1 + is2] = '\0';
	return (nstr);
}

/**
 * @brief Duplicates 'str' string by allocating new memory dynamically.
 *
 * This function duplicates the string 'str' while using malloc function 
 * to allocate memory for the new string. The new string will contain the same 
 * characters as 'str' followed by a null-terminator '\0'.  
 *
 * @param str Pointer to the source string to be duplicated.
 * @return Returns a pointer to the duplicated string or NULL if is not
 * enough memory available.
 */
char	*ft_strdup(char *str)
{
	char	*new_str;
	size_t	count;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	count = 0;
	while (str[count])
	{
		new_str[count] = str[count];
		count++;
	}
	new_str[count] = '\0';
	return (new_str);
}

/**
 * @brief Find first occurrence of a character in a string.
 *
 * The function searches for the first occurrence of the character 
 * 'chr'(converted  * to a char) in the string pointed to by 'str'. 
 * The null terminator '\0' is considered part of the string, so if 
 * 'chr' is '\0', the function returns a pointer to the null terminator.
 *
 * @param str The string to search.
 * @param chr The character to find, passed as an int but interpreted as a char.
 * @return A pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found.
 */
char	*ft_strchr(const char *str, int chr)
{
	size_t	count;
	char	urchr;

	if (!str)
		return (NULL);
	urchr = (char)chr;
	count = 0;
	while (str[count])
	{
		if (str[count] == urchr)
			return ((char *)&str[count]);
		count++;
	}
	if (urchr == '\0')
		return ((char *)&str[count]);
	return (NULL);
}

/**
 * @brief Extract a substring from a string.
 *
 * Allocates memory (using malloc(3)) and returns a substring from the string 
 * ’s’. The substring starts at index ’start’ and has a maximum length of ’len’.
 *
 * @param s The original string from which to create the substring.
 * @param start The starting index of the substring within ’s’.
 * @param len The maximum length of the substring.
 * @return The substring. NULL if the allocation fails.
 */
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	total_len;
	size_t	count;

	if (!s)
		return (NULL);
	total_len = ft_strlen(s);
	if (total_len <= start)
		return (ft_strdup(""));
	if (len > total_len - start)
		len = total_len - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	count = 0;
	while (count < len)
	{
		sub[count] = s[start + count];
		count++;
	}
	sub[count] = '\0';
	return (sub);
}
