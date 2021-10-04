/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 02:54:56 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/04 05:59:58 by spoliart         ###   ########.fr       */
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
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*test_simple_path(char *cmd, char **environ)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_path(char *cmd, char **environ)
{
	char	*path;
	char	**paths;

	if (cmd[0] && ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/'))
		return (test_simple_path(cmd, environ));
	cmd = ft_strjoin("/", cmd);
	while (environ && *environ && ft_strncmp(*environ, "PATH=", 5))
		environ++;
	paths = ft_split(*environ, "=:");
	path = test_paths(cmd, paths);
	free(cmd);
	ft_free_tab(paths);
	return (path);
}
