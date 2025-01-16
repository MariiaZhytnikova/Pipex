/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:16:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/16 15:57:58 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h> // for O_RDONLY and other flags
# include <sys/types.h>  // for pid_t
# include <sys/wait.h>  // For wait()
# include <stdio.h>      // for printf, perror, etc. DELETEEE
# include <stdlib.h>     // for exit()
# include "libft.h"

char	*get_path(char *cmd_args, char **env);
int		read_and_write(char *file_name, int act);
void	ft_free_arr(char **arr);
void	handle_exit(int code, char *name);

#endif