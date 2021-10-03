/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 02:54:56 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/03 03:55:15 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*test_paths(char *cmd, char **paths, char *cmd_copy)
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
	if (access(cmd_copy, F_OK) == 0)
		return (cmd_copy);
	return (NULL);
}

char	*get_path(char *cmd, char **environ)
{
	char	*path;
	char	*cmd_copy;
	char	**paths;

	cmd_copy = cmd;
	cmd = ft_strjoin("/", cmd);
	while (*environ && ft_strncmp(*environ, "PATH=", 5))
		environ++;
	paths = ft_split(*environ, "=:");
	path = test_paths(cmd, paths, cmd_copy);
	free(cmd);
	ft_free_tab(paths);
	if (path)
		return (path);
	return (NULL);
}
