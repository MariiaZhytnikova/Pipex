/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:55:20 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/16 15:29:27 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_exit(int code, char *name)
{
	if (code == 1)
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
	if (code == 2)
	{
		ft_putstr_fd("./pipex: command not found: ", 2);
		ft_putendl_fd(name, 2);
		return ;
	}
	if (code == 3)
	{
		ft_putstr_fd("./pipex: no such file or directory: ", 2);
		ft_putendl_fd(name, 2);
	}
	exit(1);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	read_and_write(char *file_name, int act)
{
	int	fd;
	
	if (act == 0)
		fd = open(file_name, O_RDONLY);
	if (act == 1)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (act == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND , 0777);
	if (fd < 0)
		handle_exit(3, file_name);
	return (fd);
}

static char *grab_paths(char **env)
{
	int	i;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	return (ft_memchr(env[i], '/', ft_strlen(env[i])));
}

char	*get_path(char *cmd_args, char **env)
{
	int	i;
	char **paths;
	char **args;
	char *cur_path;
	char *cur_cmd;

	i = 0;
	paths = ft_split(grab_paths(env), ':');
	args = ft_split(cmd_args, ' ');
	while (paths[i])
	{
		cur_path = ft_strjoin(paths[i++], "/");
		cur_cmd = ft_strjoin(cur_path, args[0]);
		free(cur_path);
		if (access(cur_cmd, F_OK | X_OK) == 0)
		{
			ft_free_arr(paths);
			ft_free_arr(args);
			return(cur_cmd);
		}
		free(cur_cmd);
	}
	ft_free_arr(paths);
	ft_free_arr(args);
	return (NULL);
}
