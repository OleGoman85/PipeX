/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:04:36 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/23 14:01:24 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *px_word_alloc(char *path_line, char c)
{
	int		len;
	char	*word_alloc;

	len = 0;
	while (path_line[len] != c && path_line[len]!= '\0')
		len++;
	word_alloc = px_calloc(len + 1, sizeof(char));
	while (*path_line != c && *path_line!= '\0')
		*word_alloc++ = *path_line++;
	*word_alloc = '\0';
	return (word_alloc - (len + 1));
}

static void px_split_and_alloc(char *path_line, char c, int word, char **path_arr)
{
	while (*path_line)
	{
		if (*path_line != c && *path_line)
		{
			path_arr[word] = px_alloc_word(path_line, c);
			if (!path_arr)
			{
				while (word >= 0)
				{
					free(path_arr[word]);
					word--;
				}
				free(path_arr);
			}
			while (*path_line != c && *path_line)
				path_line++;
			word++;
		}
		path_line++;
	}
	path_arr[word] = 0;
}

static int px_strcount(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str != c && *str != '\0')
		{
			count++;
			while (*str && *str != c)
				str++;
			str++;
		}
	}
	return (count);
}

char **px_split(char const *myPath, char c)
{
	int word;
	char **path_arr_empty;
	char *myPath_line;

	if (myPath == NULL)
		return (NULL);
	word = 0;
	myPath_line = (char *)myPath;
	path_arr_empty = px_calloc((px_strcount(myPath_line, c) + 1), sizeof(char *));
	px_split_and_alloc(myPath_line, c, word, path_arr_empty);
	return (path_arr_empty);
}

//     myPath_line = (char *) s;: Эта строка приводит указатель s к типу char * и присваивает его переменной str. Поскольку параметр s объявлен как char const *, он указывает на строку, которая не может быть изменена. Однако функция ft_alloc_all принимает аргумент типа char *, поэтому мы должны создать временную переменную str, чтобы мы могли изменять ее внутри функции ft_alloc_all, если это необходимо.

//     path_arr = ft_calloc((ft_strcount(str, c) + 1), sizeof(char *));: Эта строка выделяет память под массив указателей ptr, который будет содержать разделенные подстроки. Размер массива вычисляется как количество подстрок плюс один (для завершающего нулевого указателя). Функция ft_strcount используется для подсчета количества подстрок в строке str, разделенных символом c.

//     ft_alloc_all(str, c, w, ptr);: Эта строка вызывает функцию ft_alloc_all, которая разбивает строку str на подстроки, используя разделитель c, и выделяет память для каждой из этих подстрок. Результаты помещаются в массив указателей ptr.

// Таким образом, эти три строки выполняют необходимые операции для разделения строки s на подстроки, используя символ c в качестве разделителя, и возвращают массив указателей на эти подстроки.

// ft_alloc_all(str, c, w, ptr);
// myPath_line - stroka PATHA= (a tochnej, vse chto pozle)
// path_arr - massiv ukazatelej, kuda budut zapisani razdelennie stroki(poka pustoj)


