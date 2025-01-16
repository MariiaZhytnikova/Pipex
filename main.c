/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:14:20 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/16 15:17:46 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(cmd, ' ');
	path = get_path(cmd_args[0], env);
	if (!path || execve(path, cmd_args, env) == -1)
	{
		handle_exit(2, cmd_args[0]);
		ft_free_arr(cmd_args);
		exit (0);
	}
	ft_free_arr(cmd_args);
	free(path);
}

void	child(char **argv, int *pipefd, char **env)
{
	int	fd;

	fd = read_and_write(argv[1], 0);
	dup2(fd, 0);
	close(fd);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	exec(argv[2], env);
	exit(0);
}

void	parent(char **argv, int *pipefd, char **env)
{
	int	fd;

	fd = read_and_write(argv[4], 1);
	dup2(fd, 1);
	close(fd);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	close(pipefd[0]);
	exec(argv[3], env);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
		handle_exit(1, NULL);
	if (pipe(pipefd) == -1)
		exit (1);
	pid = fork();
	if (pid < 0)
		exit (1);
	if (pid == 0)
	{
		child(argv, pipefd, env);
	}
	else
	{
		parent(argv, pipefd, env);
	}
	return (0);
}

