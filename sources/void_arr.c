/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:10 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/14 14:41:19 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include "../libft/libft.h"

void	ft_init_void_arr(t_void_arr *void_arr)
{
	void_arr->size = 5;
	void_arr->to_add = 5;
	void_arr->i = 0;
	void_arr->curr = 0;
	void_arr->arr = (void **) malloc(void_arr->size * sizeof(void *));
}

void	ft_void_arr_realloc(t_void_arr *void_arr)
{
	void	*dst;

	if (!void_arr->arr || void_arr->i < void_arr->size - 1)
		return ;
	dst = (void **) malloc((void_arr->size + void_arr->to_add) * sizeof(void *));
	if (!dst)
		return (ft_free_void_arr(void_arr));
	ft_memmove(dst, void_arr->arr, void_arr->size * sizeof(void *));
	free(void_arr->arr);
	void_arr->arr = dst;
	void_arr->size += void_arr->to_add;
}

void	ft_void_arr_add(t_void_arr *void_arr, void *pointer)
{
	ft_void_arr_realloc(void_arr);
	if (!void_arr->arr)
		return ;
	void_arr->arr[void_arr->i] = pointer;
	void_arr->i++;
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
