/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:14:20 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/27 18:30:29 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid_one;
	pid_t	pid_two;

	if (argc != 5)
		handle_err("Usage: ./pipex infile cmd1 cmd2 outfile", "", 1);
	if (pipe(pipefd) == -1)
		handle_err("./pipex: Pipe creation failed", "", 1);
	pid_one = fork();
	if (pid_one < 0)
		handle_err("./pipex: Fork failed", "", 1);
	if (pid_one == 0)
		child_one(argv, pipefd, env);
	pid_two = fork();
	if (pid_two < 0)
		handle_err("./pipex: Fork failed", "", 1);
	if (pid_two == 0)
		child_two(argv, pipefd, env);
	parent(pipefd, pid_two);
	return (0);
}
