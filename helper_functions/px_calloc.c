/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:58:05 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/28 11:50:03 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*px_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		exit(2);
	px_bzero(ptr, count * size);
	return (ptr);
}
