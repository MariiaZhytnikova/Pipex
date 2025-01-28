/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:51:57 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/28 18:26:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		ft_putstr_fd("./pipex: Command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		ft_free_arr(cmd_args);
		exit (127);
	}
	ft_free_arr(cmd_args);
	free(path);
}

void	here_doc_input(char **argv, int *pipefd)
{
	char	*line;
	char	*lim;

	close(pipefd[0]);
	lim = ft_strjoin(argv[2], "\n");
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(lim);
	close(pipefd[1]);
	exit(0);
}

void	here_doc(char **argv)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		here_doc_input(argv, pipefd);
	else
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	open_pipe(char *cmd, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit (1);
	pid = fork();
	if (pid < 0)
		exit (1);
	if (pid == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		exec(cmd, env);
		exit(0);
	}
	else
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}
