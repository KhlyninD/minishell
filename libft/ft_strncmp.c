/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:05:02 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/20 15:03:19 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n > ft_strlen(s2) && ft_strlen(s2) != 0)
		n = ft_strlen(s2) + 1;
	return (ft_memcmp(s1, s2, n));
}
