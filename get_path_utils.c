/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:37:05 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/25 10:48:49 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	px_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 || *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	return (unsigned char)*s1 - (unsigned char)*s2;
}

char	*px_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	total_size;
	char	*str;
	char	*ptr;

	i = 0;
	total_size = count * size;
	ptr = (char *)malloc(total_size * sizeof(char));
	if (ptr == NULL)
		path_errors(9);
	str = ptr;
	while (i < total_size)
	{
		str[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	px_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		path_errors(10);
	while (str[i] != 0)
	{
		str++;
		i++;
	}
	return (i);
}

size_t	px_strlcpy(char *dest, const char *src, size_t size)
{
	size_t src_len;

	src_len = 0;
	if (size == 0)
		return (px_strlen(src));
	while (src[src_len] && src_len < size - 1)
	{
		dest[src_len] = src[src_len];
		src_len++;
	}
	dest[src_len] = '\0';
	while (src[src_len])
		src_len++;
	return (src_len);
}

char	*px_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		len;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = px_strlen(s1) + px_strlen(s2) + 1;
	new = (char *)calloc(len, sizeof(char));
	if (new == NULL)
		return (NULL);
	while(*s1)
	{
		new[i] = *s1;
		i++;
		s1++;
	}
	while(*s2)
	{
		new[i] = *s2;
		i++;
		s2++;
	}
	return (new);
}