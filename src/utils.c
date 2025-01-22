/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:55:20 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/22 16:43:30 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_check(char *cmd, char **env)
{
	char	**cmd_args;

	if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "yes", 3) == 0)
	{
		cmd_args = ft_split("echo y", ' ');
		if (!cmd_args)
			return (NULL);
		return (cmd_args);
	}
	else
		cmd_args = ft_split(cmd, ' ');
	if (!cmd || cmd[0] == '\0' || !cmd_args ||!cmd_args[0])
	{
		ft_free_arr(cmd_args);
		handle_error("./pipex: Command not found", "", 127);
	}
	if (!*env && !ft_strchr(cmd_args[0], '/'))
	{
		ft_free_arr(cmd_args);
		handle_error("./pipex: No PATH found", "", 127);
	}
	return (cmd_args);
}

char	*path_check(char **cmd, char **env)
{
	char	*path;

	if (!ft_strchr(cmd[0], '/'))
		return (get_path(cmd[0], env));
	path = ft_strdup(cmd[0]);
	if (!path)
		return (NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	else if (cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		ft_putstr_fd("./pipex: Permission denied for file: ", 2);
		ft_putendl_fd(path, 2);
		free(path);
		ft_free_arr(cmd);
		exit (126);
	}
	else
	{
		ft_putstr_fd("./pipex: No such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		free(path);
		ft_free_arr(cmd);
		exit (127);
	}
}

static char	*grab_paths(char **env)
{
	int	i;

	i = 0;
	while (!ft_strnstr(env[i], "MAIL", 4))
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_memchr(env[i], '/', ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

char	*access_path(char **paths, char **args)
{
	int		i;
	char	*cur_path;
	char	*cur_cmd;

	i = 0;
	while (paths[i])
	{
		cur_path = ft_strjoin(paths[i++], "/");  // Check for null
		if (!cur_path)
			return (NULL);
		cur_cmd = ft_strjoin(cur_path, args[0]);  // Check for null
		if (!cur_cmd)
			return (NULL);
		free(cur_path);
		if (access(cur_cmd, F_OK | X_OK) == 0)
			return (cur_cmd);
		free(cur_cmd);
	}
	return (NULL);
}

char	*get_path(char *cmd_args, char **env)
{
	char	**paths;
	char	**args;
	char	*cur_cmd;

	paths = ft_split(grab_paths(env), ':');
	if (!paths)
		return (NULL);
	args = ft_split(cmd_args, ' ');
	if (!args)
		return (NULL);
	cur_cmd = access_path(paths, args);
	if (!cur_cmd)
		return (ft_free_arr(paths), ft_free_arr(args), NULL);
	return (ft_free_arr(paths), ft_free_arr(args), cur_cmd);
}
