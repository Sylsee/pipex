/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:05:24 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/03 06:11:04 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	return_code()
{
	if (errno == ENOENT || errno == ENAMETOOLONG)
		return (127);
	else if (errno == EACCES)
		return (126);
	else if (errno == 0)
		return (0);
}

void	print_and_exit(char *s, int err)
{
	ft_putendl_fd(s, 2);
	exit(err);
}

void	print_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
