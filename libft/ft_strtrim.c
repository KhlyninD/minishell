/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:35:43 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/13 15:46:25 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_is_char(char s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_char(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_char(s1[end - 1], set))
		end--;
	new_s = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (start < end)
		new_s[i++] = s1[start++];
	new_s[i] = '\0';
	return (new_s);
}
