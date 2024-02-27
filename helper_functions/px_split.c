/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:58:39 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/27 10:58:42 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	px_strcount(char *s, char c)
{
	int	len;

	len = 0;
	while (*s != 0)
	{
		if (*s != c && *s)
		{
			len++;
			while (*s != 0 && *s != c)
				s++;
			continue ;
		}
		s++;
	}
	return (len);
}

static char	*px_word_alloc(char *s, char c)
{
	int		len;
	char	*ptr;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	ptr = px_calloc(len + 1, sizeof(char));
	while (*s != c && *s)
		*ptr++ = *s++;
	*ptr = 0;
	return (ptr - len);
}

static void	px_split_and_alloc(char *str, char c, int w, char **ptr)
{
	while (*str)
	{
		if (*str != c && *str)
		{
			ptr[w++] = px_word_alloc(str, c);
			if (!ptr)
			{
				while (w >= 0)
					free(ptr[w--]);
				free(ptr);
			}
			while (*str != c && *str)
				str++;
			continue ;
		}
		str++;
	}
	ptr[w] = 0;
}

char	**px_split(char const *s, char c)
{
	int		w;
	char	**ptr;
	char	*str;

	if (!s)
		return (NULL);
	w = 0;
	str = (char *) s;
	ptr = px_calloc((px_strcount(str, c) + 1), sizeof(char *));
	px_split_and_alloc(str, c, w, ptr);
	return (ptr);
}