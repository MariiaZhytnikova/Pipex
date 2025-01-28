/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:14:20 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:39 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(int argc, char **argv)
{
	int	out_fd;

	out_fd = read_and_write(argv[argc - 1], 2);
	if (dup2(out_fd, 1) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(out_fd) == -1)
		handle_err("./pipex: Close failed", "", 1);
	here_doc(argv);
}

void	handle_no_doc(int argc, char **argv)
{
	int	in_fd;
	int	out_fd;

	in_fd = read_and_write(argv[1], 0);
	if (dup2(in_fd, 0) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(in_fd) == -1)
		handle_err("./pipex: Close failed", "", 1);
	out_fd = read_and_write(argv[argc - 1], 1);
	if (dup2(out_fd, 1) == -1)
		handle_err("./pipex: dup2 failed", "", 1);
	if (close(out_fd) == -1)
		handle_err("./pipex: Close failed", "", 1);
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	if (argc < 5)
		handle_err("Usage: ./pipex infile cmd| ... |cmd outfile", "", 1);
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
	{
		if (argc < 6)
			handle_err("Usage: ./pipex here_doc in cmd |...| cmd out", "", 1);
		i = 3;
		handle_here_doc(argc, argv);
	}
	else
	{
		i = 2;
		handle_no_doc(argc, argv);
	}
	while (i < argc - 2)
		open_pipe(argv[i++], env);
	exec(argv[argc - 2], env);
	while (argc - 3 > 0)
	{
		wait(NULL);
		argc--;
	}
	return (0);
}
