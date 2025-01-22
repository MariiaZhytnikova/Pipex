/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:28 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/22 15:37:49 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(char *msg, char *var, int code)
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
