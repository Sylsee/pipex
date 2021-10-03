/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 02:54:56 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/03 05:07:28 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*test_paths(char *cmd, char **paths)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				errno = 0;
				return (path);
			}
			errno = EACCES;
		}
		free(path);
	}
	return (NULL);
}

char	*test_simple_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*get_path(char *cmd, char **environ)
{
	char	*path;
	char	**paths;

	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		path = test_simple_path(cmd);
		dprintf(2, "slt\n");
		if (!path)
			dprintf(2, "errno: [%d]\n", errno);
		return (NULL);
	}
	cmd = ft_strjoin("/", cmd);
	while (environ && *environ && ft_strncmp(*environ, "PATH=", 5))
		environ++;
	paths = ft_split(*environ, "=:");
	path = test_paths(cmd, paths);
	free(cmd);
	ft_free_tab(paths);
	return (path);
}
