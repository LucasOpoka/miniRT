/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:10 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/09 22:57:29 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

int	ft_init_void_arr(t_void_arr *void_arr)
{
	void_arr->size = 5;
	void_arr->to_add = 5;
	void_arr->i = 0;
	void_arr->arr = (void **) malloc(void_arr->size * sizeof(void *));
	return (void_arr->arr != NULL);
}

int	ft_void_arr_realloc(t_void_arr *void_arr)
{
	void	*dst;

	if (!void_arr->arr)
		return (0);
	if (void_arr->i < void_arr->size - 1)
		return (1);
	dst = malloc((void_arr->size + void_arr->to_add) * sizeof(void *));
	if (!dst)
	{
		ft_free_void_arr(void_arr);
		return (0);
	}
	ft_memmove(dst, void_arr->arr, void_arr->size * sizeof(void *));
	free(void_arr->arr);
	void_arr->arr = dst;
	void_arr->size += void_arr->to_add;
	return (1);
}

int	ft_void_arr_add(t_void_arr *void_arr, void *pointer)
{
	if (!ft_void_arr_realloc(void_arr))
		return (0);
	void_arr->arr[void_arr->i] = pointer;
	void_arr->i++;
	return (1);
}

void	ft_free_void_arr(t_void_arr *void_arr)
{
	size_t	i;

	if (!void_arr->arr)
		return ;
	i = 0;
	while (i < void_arr->i)
		free(void_arr->arr[i++]);
	free(void_arr->arr);
	void_arr->arr = 0;
}
