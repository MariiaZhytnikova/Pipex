/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:16:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/27 19:00:51 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

void	ft_free_arr(char **arr);
void	qu_error(char *msg, char *var, int code);
void	handle_err(char *msg, char *var, int code);
int		wordcount(char *str);
int		skip_quotes(char *str, int i);
int		quotes_balanced(const char *str);
void	qu_split(char **res, char *cmd, int k);
int		command_in_quotes(char *str);
void	check_quotes(char **str);
char	**cmd_check(char *cmd, char **env);
char	*path_check(char **cmd, char **env);
int		read_and_write(char *file_name, int act);
void	exec(char *cmd, char **env);
void	here_doc(char **argv);
void	open_pipe(char *cmd, char **env);

#endif
