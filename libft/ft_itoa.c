/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:32:02 by mvenmo            #+#    #+#             */
/*   Updated: 2021/11/09 14:21:47 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(long int n)
{
	int		sign;
	char	c[20];
	int		i;
	int		j;
	char	*str;

	sign = 1;
	if (n < 0)
		sign = -1;
	i = 0;
	while (n != 0 || i == 0)
	{
		c[i++] = n % 10 * sign + '0';
		n /= 10;
	}
	if (sign == -1)
		c[i++] = '-';
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	j = 0;
	while (--i >= 0)
		str[j++] = c[i];
	str[j] = '\0';
	return (str);
}
