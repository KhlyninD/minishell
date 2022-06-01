/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:44:54 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/20 12:28:24 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(char *s);

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	str += ft_strlen(str) + 1;
	while (str-- != s)
		if ((unsigned char)*str == (unsigned char) c)
			return (str);
	return (NULL);
}
