/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:35:33 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/15 14:50:55 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		cmp;

	i = 0;
	while (i < n)
	{		
		cmp = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (cmp != 0)
			return (cmp);
		i++;
	}
	return (0);
}
