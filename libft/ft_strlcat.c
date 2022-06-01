/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:09:01 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/17 16:11:04 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(dst);
	if (size > len)
		return (len + ft_strlcpy(dst + len, src, size - len));
	return (size + ft_strlen(src));
}
