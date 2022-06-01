/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 08:44:10 by mvenmo            #+#    #+#             */
/*   Updated: 2021/10/21 11:40:45 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

static char	**res_realloc(char **res, unsigned int i)
{
	char			**res2;

	res2 = malloc((i + 1) * sizeof(*res));
	if (res2 == NULL)
		return (NULL);
	res2[i] = NULL;
	while (i-- > 0)
		res2[i] = res[i];
	free(res);
	return (res2);
}

static char	**free_and_null(char **res, unsigned int i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
	return (NULL);
}

static void	s_plusplus_len_plusplus(const char **s, size_t *len)
{
	(*s)++;
	(*len)++;
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	i;
	size_t			len;

	if (s != NULL)
		res = malloc((ft_strlen(s) / 2 + 1) * sizeof(*res));
	if (s == NULL || res == NULL)
		return (NULL);
	len = 0;
	i = 0;
	while (*s)
	{
		while (*s != c && *s)
			s_plusplus_len_plusplus(&s, &len);
		if (len != 0)
		{
			res[i++] = ft_substr(s - len, 0, len);
			len = 0;
			if (res[i - 1] == NULL)
				return (free_and_null(res, i - 1));
		}
		else
			s++;
	}
	return (res_realloc(res, i));
}
