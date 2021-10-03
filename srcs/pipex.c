/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 08:28:42 by spoliart          #+#    #+#             */
/*   Updated: 2021/10/03 04:17:16 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(int fd[2], int fd_infile, char **command[2], char **envp)
{
	int		err;
	char	*path;

	err = 1;
	dup2(fd[1], 1);
	dup2(fd_infile, 0);
	close(fd[0]);
	close(fd[1]);
	path = get_path(command[0][0], envp);
	if (path)
		execve(path, command[0], envp);
	else
	{
		err = 127;
		ft_putstr_fd(command[0][0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	free(path);
	if (command[1])
		ft_free_tab(command[1]);
	ft_free_tab(command[0]);
	close(fd_infile);
	exit(err);
}

void	parent(int fd[2], int fd_outfile, char **command[2], char **envp)
{
	int		err;
	char	*path;

	err = 1;
	dup2(fd[0], 0);
	dup2(fd_outfile, 1);
	close(fd[0]);
	close(fd[1]);
	path = get_path(command[1][0], envp);
	if (path)
		execve(path, command[1], envp);
	else
	{
		err = 127;
		ft_putstr_fd(command[1][0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	free(path);
	if (command[0])
		ft_free_tab(command[0]);
	ft_free_tab(command[1]);
	close(fd_outfile);
	exit(err);
}

void	pipex(char **commands[2], int fd[2], char **envp)
{
	int		fd_pipe[2];
	pid_t	child_pid;

	if (pipe(fd_pipe) != 0)
	{
		ft_free_tab(commands[0]);
		ft_free_tab(commands[1]);
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		ft_free_tab(commands[0]);
		ft_free_tab(commands[1]);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		child(fd_pipe, fd[0], commands, envp);
	else
		parent(fd_pipe, fd[1], commands, envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	char	**args[2];

	if (argc != 5)
		return (1);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd[0] < 0)
		print_error(argv[1]);
	if (fd[1] < 0)
		print_error(argv[4]);
	if (fd[0] < 0 || fd[1] < 0)
		exit(1);
	args[0] = ft_split(argv[2], " ");
	args[1] = ft_split(argv[3], " ");
	pipex(args, fd, envp);
	return (0);
}
