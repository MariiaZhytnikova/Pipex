/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:28 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/27 19:02:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	qu_error(char *msg, char *var, int code)
{
	char	*ms;
	int		start;
	int		end;

	end = 0;
	start = 0;
	while (var[end])
	{
		if (var[end] == '\'')
		{
			start = end + 1;
			end = skip_quotes(var + end, start);
			break ;
		}
		end++;
	}
	ms = ft_substr(var, start, end - start);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(ms, 2);
	free(var);
	free(ms);
	exit(code);
}

void	handle_err(char *msg, char *var, int code)
{
	ft_putstr_fd(msg, 2);
	if (var[0])
		ft_putendl_fd(var, 2);
	else
		ft_putstr_fd("\n", 2);
	exit(code);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	quotes_balanced(const char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote_count++;
		i++;
	}
	return (quote_count % 2 == 0);
}

int	command_in_quotes(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] <= 32)
			return (-1);
		if (str[i] == '\'')
			return (i);
		i++;
	}
	return (0);
}
