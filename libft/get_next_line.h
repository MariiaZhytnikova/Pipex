/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:45 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/16 16:05:04 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h> 
# include <stdint.h>

char	*get_next_line(int fd);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(char const *s1, char const *s2);
void	*gnl_calloc(size_t num, size_t size);
void	read_from_file(char **big_buffer, int fd);
void	ft_line_res(char **big_buffer, char **line, size_t line_len);

#endif
