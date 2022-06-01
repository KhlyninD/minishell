/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:29:08 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/13 11:29:13 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	cmp;

	while (1)
	{
		cmp = (unsigned char) *s1 - (unsigned char) *s2;
		if (cmp || *s1++ == '\0' || *s2++ == '\0')
			return (cmp);
	}
}