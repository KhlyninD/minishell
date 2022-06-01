/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:15:21 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/11 11:20:12 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_str_array(char **array, char **copy)
{
	int		i;

	if (!array)
		return (NULL);
	if (!copy)
	{
		i = 0;
		while (array[i])
			i++;
		copy = malloc((i + 1) * sizeof(*copy));
		if (!copy)
			return (NULL);
	}
	i = -1;
	while (array[++i])
		copy[i] = ft_strdup(array[i]);
	copy[i] = NULL;
	return (copy);
}

char	**ft_insert_str_to_array(char ***array_pointer, char *str)
{
	int		i;
	char	**array;
	char	**copy;

	if (array_pointer == NULL || *array_pointer == NULL)
		return (NULL);
	array = *array_pointer;
	i = 0;
	while (array[i])
		i++;
	copy = malloc((i + 2) * sizeof(*copy));
	if (!copy)
		return (NULL);
	i = -1;
	while (array[++i])
		copy[i] = array[i];
	copy[i] = str;
	copy[i + 1] = NULL;
	free(array);
	*array_pointer = copy;
	return (copy);
}

char	**ft_delete_from_array(char **array, const char *str)
{
	int	i;
	int	j;

	if (array == NULL || str == NULL)
		return (NULL);
	i = -1;
	while (array[++i])
	{
		if (!ft_strcmp(array[i], str))
		{
			free(array[i]);
			array[i] = array[i + 1];
			j = i - 1;
			while (array[++j])
				array[j] = array[j + 1];
			i--;
		}
	}
	return (array);
}

void	free_str_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (tmp == NULL)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}
