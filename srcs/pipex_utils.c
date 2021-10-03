/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 02:54:56 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/03 06:51:52 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*test_paths(char *cmd, char **paths)
{
	int ret;
	int		i;
	char	*path;

	i = 0;
	dprintf(2, "cmd: [%s]\n", cmd);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd);
		if ((ret = access(path, X_OK)) == 0)
			return (path);
		dprintf(2, "paths: [%s]\nret: [%d]\nerrno: [%d]\n", paths[i], ret, errno);
		free(path);
	}
	return (NULL);
}

char	*test_simple_path(char *cmd)
{
	//int ret;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	//dprintf(2, "jcmd: [%s]\njret: [%d]\njerrno: [%d]\n", cmd, ret, errno);
	return (NULL);
}

char	*get_path(char *cmd, char **environ)
{
	char	*path;
	char	**paths;

	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
		return (test_simple_path(cmd));
	cmd = ft_strjoin("/", cmd);
	while (environ && *environ && ft_strncmp(*environ, "PATH=", 5))
		environ++;
	paths = ft_split(*environ, "=:");
	path = test_paths(cmd, paths);
	free(cmd);
	ft_free_tab(paths);
	return (path);
}
