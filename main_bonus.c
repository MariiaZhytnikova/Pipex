/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:14:20 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/16 18:10:52 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		exit (1);
	}
	ft_free_arr(cmd_args);
	free(path);
}

void	here_doc_input(char **argv, int *pipefd)
{
	char	*line;

	close(pipefd[0]); // Close pipes read, we need write
	while (1)
	{
		line = get_next_line(0); // Read from stdin
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pipefd[1]); // send it to parent frought pipe
		free(line);
	}
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
	if (pid == 0) // Child process
	{	here_doc_input(argv, pipefd);  // Input stream should be from std in
		close(pipefd[0]);
		exit (0);
	}
	else		// Parent process
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
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
	if (pid == 0) // CHILD
	{
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
		exec(cmd, env);
		exit(0);
	}
	else // PARENT // CHILDRENS DO ALL JOB
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	in_fd;
	int	out_fd;
	int	i;

	if (argc < 5)
		handle_exit(1, NULL);
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
	{
		if (argc < 6)
			handle_exit(1, NULL);
		i = 3;
		out_fd = read_and_write(argv[argc - 1], 2); //2 APPEND // We have no input file we have stdin
		here_doc(argv);
	}
	else
	{
		i = 2; // We have input file
		in_fd = read_and_write(argv[1], 0); //0 READ
		out_fd = read_and_write(argv[argc - 1], 1); //3 TRUNCATE //
		dup2(in_fd, 0);
		close(in_fd);
	}
	while (i < argc - 2)
		open_pipe(argv[i++], env); // Creating of new pair
	dup2(out_fd, 1); // Parent process for last command
	close(out_fd);
	exec(argv[argc - 2], env);
	i = 0;
	while (i++ < argc - 3)
		wait(NULL);
	return (0);
}