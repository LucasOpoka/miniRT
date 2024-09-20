/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comps2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:28:57 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 16:31:46 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_set_refr_ind(double *n, t_xs *containers);
void	ft_get_refr_ind(t_comps *comps, t_xs *xs, t_intrsc *hit);
int		ft_containers_include(t_xs *containers, t_obj *obj);
void	ft_remove_container(t_xs *containers, t_intrsc *curr);
void	ft_get_schlick(t_comps *comps);

void	ft_set_refr_ind(double *n, t_xs *containers)
{
	if (containers->i == 0)
		*n = 1;
	else
		*n = containers->arr[containers->i - 1].obj->refractive;
}

// Test to get n1 and n2
void	ft_get_refr_ind(t_comps *comps, t_xs *xs, t_intrsc *hit)
{
	size_t		i;
	t_intrsc	*curr;
	t_xs		*containers;

	i = 0;
	containers = &xs[1];
	containers->i = 0;
	while (i < xs->i && containers->arr)
	{
		curr = (t_intrsc *) &xs->arr[i++];
		if (curr == hit)
			ft_set_refr_ind(&comps->n1, containers);
		if (ft_containers_include(containers, curr->obj))
			ft_remove_container(containers, curr);
		else
			ft_add_intersection(containers, curr->obj, curr->t);
		if (curr == hit)
			ft_set_refr_ind(&comps->n2, containers);
	}
}

int	ft_containers_include(t_xs *containers, t_obj *obj)
{
	size_t	i;

	i = 0;
	while (i < containers->i)
	{
		if (obj == containers->arr[i].obj)
			return (1);
		i++;
	}
	return (0);
}

void	ft_remove_container(t_xs *containers, t_intrsc *curr)
{
	size_t		reader;
	size_t		writer;
	t_intrsc	intr;

	if (!containers->arr)
		return ;
	reader = 0;
	writer = 0;
	while (reader < containers->i)
	{
		intr = containers->arr[reader];
		if (curr->obj != intr.obj)
			containers->arr[writer++] = containers->arr[reader];
		reader++;
	}
	containers->i -= 1;
}

void	ft_get_schlick(t_comps *comps)
{
	double	cos;
	double	n;
	double	sin2_t;
	double	r0;

	cos = ft_vct_dot(&comps->eye, &comps->normal);
	if (comps->n1 > comps->n2)
	{
		n = comps->n1 / comps->n2;
		sin2_t = pow(n, 2) * (1 - pow(cos, 2));
		if (sin2_t > 1)
		{
			comps->schlick = 1;
			return ;
		}
		cos = sqrt(1 - sin2_t);
	}
	r0 = pow((comps->n1 - comps->n2) / (comps->n1 + comps->n2), 2);
	comps->schlick = r0 + (1 - r0) * pow(1 - cos, 5);
}
