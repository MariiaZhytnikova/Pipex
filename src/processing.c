/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:51:57 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/22 19:28:00 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_and_write(char *file_name, int act)
{
	int	fd;

	if (act == 0)
	{
		if (access(file_name, R_OK) != 0)
			handle_error("./pipex: Failed to read, Permission denied: ", \
			file_name, 127);
		else
			fd = open(file_name, O_RDONLY);
	}
	if (act == 1)
	{
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
			handle_error("./pipex: Failed to write, Permission denied: ", \
			file_name, 1);
		else
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (fd < 0)
		handle_error("./pipex: No such file or directory: ", file_name, 127);
	return (fd);
}

void	exec(char *cmd, char **env)
{
	char	**cmd_args;
	char	*path;

	cmd_args = cmd_check(cmd, env);
	if (!cmd_args)
		handle_error("./pipex: Failed to get command: ", cmd, 1);
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

void	child_one(char **argv, int *pipefd, char **env)
{
	int	fd;

	if (dup2(pipefd[1], 1) == -1)
		handle_error("./pipex: dup2 failed", "", 1);
	if (close(pipefd[0]) == -1)
		handle_error("./pipex: Close failed", "", 1);
	if (close(pipefd[1]) == -1)
		handle_error("./pipex: Close failed", "", 1);
	fd = read_and_write(argv[1], 0);
	if (dup2(fd, 0) == -1)
		handle_error("./pipex: dup2 failed", "", 1);
	if (close(fd) == -1)
		handle_error("./pipex: Close failed", "", 1);
	exec(argv[2], env);
}

void	child_two(char **argv, int *pipefd, char **env)
{
	int	fd;

	if (dup2(pipefd[0], 0) == -1)
		handle_error("./pipex: dup2 failed", "", 1);
	if (close(pipefd[1]) == -1)
		handle_error("./pipex: Close failed", "", 1);
	if (close(pipefd[0]) == -1)
		handle_error("./pipex: Close failed", "", 1);
	fd = read_and_write(argv[4], 1);
	if (dup2(fd, 1) == -1)
		handle_error("./pipex: dup2 failed", "", 1);
	if (close(fd) == -1)
		handle_error("./pipex: Close failed", "", 1);
	exec(argv[3], env);
}


void	parent(int *pipefd, int pid_one, int pid_two)
{
	int		status1;
	int		status2;
	
	// (void)pid_one;
	// (void)pid_two;
	if (close(pipefd[1]) == -1)
		handle_error("./pipex: Close failed", "", 1);
	if (close(pipefd[0]) == -1)
		handle_error("./pipex: Close failed", "", 1);
	// if (wait(&status) == -1)
	// 	handle_error("./pipex: Waitpid failed", "", 1);

	//while(waitpid(-1, NULL, 0) > 0);
	if (waitpid(pid_one, &status1, 0) == -1)
		handle_error("./pipex: Waitpid failed", "", 1);
	if (waitpid(pid_two, &status2, 0) == -1)
		handle_error("./pipex: Waitpid failed", "", 1);
	// if (WIFEXITED(status2) && WIFEXITED(status1))
	// 	exit (WIFEXITED(status2));
	exit(WIFEXITED(status2) ? WEXITSTATUS(status2) : WEXITSTATUS(status1));
	// 	printf("Child 1 exited with status %d\n", WEXITSTATUS(status1));
	// 	printf("Child 2 exited with status %d\n", WEXITSTATUS(status2));
	// exit(status2 >> 8 & 255);
}

    // Wait for both child processes
    if (waitpid(pid_one, &status1, 0) == -1)
        handle_error("./pipex: Waitpid failed", "", 1);
    if (waitpid(pid_two, &status2, 0) == -1)
        handle_error("./pipex: Waitpid failed", "", 1);

    // Check exit statuses and exit accordingly
    if (WIFEXITED(status1) && WIFEXITED(status2)) {
        exit(WEXITSTATUS(status1) == 0 ? WEXITSTATUS(status2) : WEXITSTATUS(status1));
    } else {
        exit(1); // If any child did not exit normally
    }
1. Signal Handling: Consider implementing signal handling for SIGCHLD to automatically reap child processes when they terminate. This can help prevent zombies without requiring explicit wait() calls.
