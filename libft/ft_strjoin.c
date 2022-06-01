/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:28:56 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/15 16:35:45 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (s == NULL)
		return (NULL);
	res = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (res);
}
