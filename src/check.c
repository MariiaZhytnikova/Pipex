/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:23:12 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/28 18:00:13 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_quotes(char **str)
{
	int		i;
	char	*temp;

	if (!quotes_balanced(*str))
		handle_err("./pipex: interactive prompt is not implemented", "", 1);
	else
	{
		i = 0;
		temp = ft_strdup(*str);
		if (!temp)
			return ;
		while (temp[i] && temp[i] == ' ')
			i++;
		if (temp[i] == '\'' && temp[i + 1])
		{
			if (command_in_quotes(temp + i) == -1)
			{
				free(*str);
				qu_error("./pipex: command not found: ", temp, 1);
			}
		}
		free(temp);
	}
}

char	**cmd_check(char *cmd, char **env)
{
	char	**cmd_args;
	int		wc;
	char	*str;

	if (!cmd || cmd[0] == '\0')
		handle_err("./pipex: permission denied:", "", 127);
	str = ft_strdup(cmd);
	if (!str)
		return (NULL);
	check_quotes(&str);
	wc = wordcount(str);
	if (wc == 0)
		return (free(str), NULL);
	cmd_args = (char **)ft_calloc(wc + 1, sizeof(char *));
	qu_split(cmd_args, str, 0);
	if (!cmd_args || !cmd_args[0])
		return (free(str), NULL);
	free(str);
	if (!cmd_args[0] || (!*env && !ft_strchr(cmd_args[0], '/')))
	{
		ft_putstr_fd("./pipex: command not found:\n", 2);
		ft_free_arr(cmd_args);
		exit (127);
	}
	return (cmd_args);
}
