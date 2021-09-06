/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 02:54:56 by spoliart          #+#    #+#             */
/*   Updated: 2021/09/06 03:42:59 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*test_paths(char *cmd, char **paths, char *cmdCopy)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	if (access(cmdCopy, F_OK) == 0)
		return (cmdCopy);
	return (NULL);
}

char	*get_path(char *cmd, char **environ)
{
	char	*path;
	char	*cmdCopy;
	char	**paths;

	cmdCopy = cmd;
	cmd = ft_strjoin("/", cmd);
	while (*environ && ft_strncmp(*environ, "PATH=", 5))
		environ++;
	paths = ft_split(*environ, "=:");
	path = test_paths(cmd, paths, cmdCopy);
	free(cmd);
	ft_free_tab(paths);
	if (path)
		return (path);
	return (NULL);
}
