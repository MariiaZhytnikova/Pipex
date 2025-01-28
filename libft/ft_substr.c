/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:14:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/01/27 16:30:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	fact_len;

	if (!s)
		return (0);
	fact_len = ft_strlen(s);
	if (fact_len < start)
		return (ft_strdup(""));
	if (fact_len - start < len)
		len = fact_len - start;
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len && start + i < fact_len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
