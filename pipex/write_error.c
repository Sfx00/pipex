/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:38:18 by obajali           #+#    #+#             */
/*   Updated: 2025/01/07 15:39:36 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_error(char *file, char *str)
{
	int	i;

	i = 0;
	if (file)
	{
		write(2, file, ft_strlen(file));
		write(1, ": ", 2);
	}
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
}
