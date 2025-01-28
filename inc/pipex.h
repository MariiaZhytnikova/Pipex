/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:16:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/27 18:32:02 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
void	child_one(char **argv, int *pipefd, char **env);
void	child_two(char **argv, int *pipefd, char **env);
void	parent(int *pipefd, int pid_two);

#endif
