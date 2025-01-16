/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:14:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/15 10:23:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_split(char **dest)
{
	size_t	i;

	if (!dest)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}

static size_t	ft_wrdc(const char *str, char delimiter)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delimiter && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == delimiter)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*ft_strcpy(char *start, char *end)
{
	size_t		i;
	size_t		len;
	char		*res;

	i = 0;
	len = end - start;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = start[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**ft_split_processing(char **dest, char const *str, char c)
{
	size_t		index;
	char		*ptr_start;

	index = 0;
	ptr_start = NULL;
	while (*str)
	{
		if (*str != c && !ptr_start)
			ptr_start = (char *)str;
		else if (*str == c && ptr_start)
		{
			dest[index++] = ft_strcpy(ptr_start, (char *)str);
			if (!dest[index - 1])
				return (ft_free_split(dest));
			ptr_start = NULL;
		}
		str++;
	}
	if (ptr_start)
		dest[index++] = ft_strcpy(ptr_start, (char *)str);
	if (!dest[index - 1])
		return (ft_free_split(dest));
	dest[index] = NULL;
	return (dest);
}

char	**ft_split(char const *str, char c)
{
	char	**dest;
	size_t	num;

	if (!str)
		return (NULL);
	num = ft_wrdc(str, c);
	if (num == 0)
	{
		dest = (char **)malloc(sizeof(char *));
		if (!dest)
			return (NULL);
		dest[0] = NULL;
		return (dest);
	}
	dest = (char **)malloc(sizeof(char *) * (num + 1));
	if (!dest)
		return (NULL);
	if (!ft_split_processing(dest, str, c))
		return (ft_free_split(dest));
	return (dest);
}
