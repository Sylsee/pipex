/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 08:03:21 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/23 23:12:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

char	*get_path(char *tmp, char **environ);
void	print_and_exit(char *s, int err);
void	print_error(char *s);

#endif
