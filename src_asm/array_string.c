/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:41:43 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:41:44 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_array_string		*new_array_string(size_t size)
{
	t_array_string	*arr;

	if ((arr = (t_array_string *)malloc(sizeof(t_array_string))) == NULL)
		return (NULL);
	if ((arr->arr = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
	{
		free(arr);
		print_error("failed to allocate memory", NULL);
		exit(2);
	}
	arr->i = 0;
	ft_bzero(arr->arr, sizeof(char *) * (size + 1));
	arr->size = size;
	return (arr);
}

static int			realloc_array_string(t_array_string *arr)
{
	char	**new;
	int		i;

	i = 0;
	if ((new = (char **)malloc(sizeof(char *) * arr->size * 2)) == NULL)
	{
		print_error("failed to allocate memory", NULL);
		exit(2);
	}
	ft_bzero(new, sizeof(char *) * arr->size * 2);
	while (i < arr->i)
	{
		new[i] = ft_strdup(arr->arr[i]);
		free(arr->arr[i]);
		i++;
	}
	free(arr->arr);
	arr->arr = new;
	arr->size = arr->size * 2;
	return (1);
}

void				del_array_string(t_array_string **arr)
{
	int		i;

	i = 0;
	if (arr != NULL)
	{
		while (i < (*arr)->i)
		{
			if ((*arr)->arr[i])
				free((*arr)->arr[i]);
			i++;
		}
		free((*arr)->arr);
		(*arr)->arr = NULL;
		free(*arr);
		*arr = NULL;
	}
}

int					add_str_to_array_string(t_array_string *arr, char *str)
{
	if (arr->i + 1 >= (int)arr->size)
		realloc_array_string(arr);
	if (arr->arr == NULL)
	{
		print_error("failed to allocate memory", NULL);
		exit(2);
	}
	arr->arr[arr->i] = str;
	arr->i++;
	return (1);
}

void				print_string(t_array_string *arr)
{
	int		i;

	i = 0;
	if (arr != NULL)
	{
		while (i < arr->i)
		{
			ft_printf("%s ", arr->arr[i]);
			i++;
		}
	}
}
