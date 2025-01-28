/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:51:57 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/28 17:59:44 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**cmd_args;
	char	*path;

	cmd_args = cmd_check(cmd, env);
	if (!cmd_args)
		handle_err("./pipex: command not found: ", cmd, 127);
	path = path_check(cmd_args, env);
	if (!path || execve(path, cmd_args, env) == -1)
	{
		ft_putstr_fd("./pipex: command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		ft_free_arr(cmd_args);
		exit (127);
	}
	ft_free_arr(cmd_args);
	free(path);
}

void	child_one(char **argv, int *pipefd, char **env)
{
	int	fd;

	if (dup2(pipefd[1], 1) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(pipefd[0]) == -1)
		handle_err("./pipex: close failed", "", 1);
	if (close(pipefd[1]) == -1)
		handle_err("./pipex: close failed", "", 1);
	fd = read_and_write(argv[1], 0);
	if (dup2(fd, 0) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(fd) == -1)
		handle_err("./pipex: close failed", "", 1);
	exec(argv[2], env);
}

void	child_two(char **argv, int *pipefd, char **env)
{
	int	fd;

	if (dup2(pipefd[0], 0) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(pipefd[1]) == -1)
		handle_err("./pipex: close failed", "", 1);
	if (close(pipefd[0]) == -1)
		handle_err("./pipex: close failed", "", 1);
	fd = read_and_write(argv[4], 1);
	if (dup2(fd, 1) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(fd) == -1)
		handle_err("./pipex: close failed", "", 1);
	exec(argv[3], env);
}

void	parent(int *pipefd, int pid_two)
{
	int		i;
	int		status;
	pid_t	pid;
	int		final;

	if (close(pipefd[1]) == -1)
		handle_err("./pipex: close failed", "", 1);
	if (close(pipefd[0]) == -1)
		handle_err("./pipex: close failed", "", 1);
	i = 0;
	while (i < 2)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			exit(1);
		if (WIFEXITED(status))
		{
			if (pid == pid_two)
				final = status;
		}
		i++;
	}
	exit(WEXITSTATUS(final));
}
