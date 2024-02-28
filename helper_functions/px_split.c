/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:58:39 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/28 11:35:47 by ogoman           ###   ########.fr       */
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
	char	*word;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	word = px_calloc(len + 1, sizeof(char));
	while (*s != c && *s)
		*word++ = *s++;
	*word = 0;
	return (word - len);
}

static void	px_split_and_alloc(char *str, char c, int word, char **ptr)
{
	while (*str)
	{
		if (*str != c && *str)
		{
			ptr[word++] = px_word_alloc(str, c);
			if (!ptr)
			{
				while (word >= 0)
					free(ptr[word--]);
				free(ptr);
			}
			while (*str != c && *str)
				str++;
			continue ;
		}
		str++;
	}
	ptr[word] = NULL;
}

char	**px_split(char const *s, char c)
{
	int		word;
	char	**ptr;
	char	*str;

	if (!s)
		return (NULL);
	word = 0;
	str = (char *) s;
	ptr = px_calloc((px_strcount(str, c) + 1), sizeof(char *));
	px_split_and_alloc(str, c, word, ptr);
	return (ptr);
}
