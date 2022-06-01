/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:07:23 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/17 16:35:21 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (little[0] == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		k = i;
		j = 0;
		while (big[k] == little[j])
		{
			k++;
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
			if (big[k] == '\0' || (k == len))
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
