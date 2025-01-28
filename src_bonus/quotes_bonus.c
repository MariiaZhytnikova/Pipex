/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:36:10 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:07 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	skip_quotes(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

int	wordcount(char *str)
{
	int	count;
	int	i[2];

	i[0] = 0;
	count = 0;
	i[1] = 1;
	while (str[i[0]])
	{
		if (str[i[0]] == '\'')
		{
			count++;
			i[0] = skip_quotes(str, i[0]);
		}
		else if ((str[i[0]] != ' ' && str[i[0]] != '\n') && i[1] == 1)
		{
			count++;
			i[1] = 0;
		}
		else if ((str[i[0]] == ' ' || str[i[0]] == '\n') && i[1] == 0)
			i[1] = 1;
		else if (str[i[0]] == '\\' && str[i[0] + 1] == ' ')
			i[0]++;
		i[0]++;
	}
	return (count);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	no_qu(char *cmd, int *end)
{
	while (cmd[*end] && (cmd[*end] != ' ' && cmd[*end] != '\''))
	{
		if (cmd[*end] == '\\' && cmd[*end + 1] == ' ')
			(*end)++;
		(*end)++;
	}
}

void	qu_split(char **res, char *cmd, int k)
{
	int	start;
	int	end;

	start = 0;
	end = skip_spaces(cmd);
	if (!cmd[end])
		return ;
	if (cmd[end] == '\'' && cmd[end + 1])
	{
		start = end + 1;
		end = skip_quotes(cmd, end);
	}
	else if (cmd[end])
	{
		start = end;
		no_qu(cmd, &end);
	}
	res[k] = ft_substr(cmd, start, end - start);
	if (!res[k])
		return (ft_free_arr(res));
	if (cmd[end] == '\'' && cmd[end + 1])
		end++;
	if (cmd[end] && cmd[end] != '\'')
		qu_split(res, &cmd[end], k + 1);
}
