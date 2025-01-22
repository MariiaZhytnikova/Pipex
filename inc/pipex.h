/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:16:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/22 18:53:25 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <fcntl.h> // for O_RDONLY and other flags
# include <sys/types.h>  // for pid_t
# include <sys/wait.h>  // For wait()
# include <stdio.h>      // for printf, perror, etc. DELETEEE
# include <stdlib.h>     // for exit()
# include "libft.h"

void	ft_free_arr(char **arr);
void	handle_error(char *msg, char *var, int code);
char	**cmd_check(char *cmd, char **env);
char	*path_check(char **cmd, char **env);
char	*get_path(char *cmd_args, char **env);
int	read_and_write(char *file_name, int act);
void	exec(char *cmd, char **env);
void	child_one(char **argv, int *pipefd, char **env);
void	child_two(char **argv, int *pipefd, char **env);
void	parent(int *pipefd, int pid_one, int pid_two);

#endif
