/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:28:57 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/31 17:49:56 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"


void	ft_get_schlick(t_comps *comps);
t_vct	ft_under_point(const t_vct *point, const t_vct *normal);
int		ft_containers_include(t_void_arr *containers, t_shape *shape);
void	ft_remove_container(t_void_arr *containers, t_intersection *curr);
void	ft_get_refr_ind(t_comps *comps, t_void_arr *intersections, t_intersection *closest);

// prepare_computations - The Ray Tracer Challenge p.76 p.93
void	ft_prepare_computations(t_comps *comps, t_intersection *closest, const t_ray *ray, t_void_arr *intersections)
{
	comps->t = closest->t;
	comps->shape = closest->shape;
	comps->point = ft_ray_point(ray, comps->t); 
	comps->eye = ft_vct_neg(&ray->D);
	comps->eye.w = 0;
	ft_get_shape_normal_and_color(comps);
	comps->inside = 0;
	if (ft_vct_dot(&comps->normal, &comps->eye) < 0)
	{
		comps->inside = 1;
		comps->normal = ft_vct_neg(&comps->normal);
	}
	comps->reflect = ft_reflect(&ray->D, &comps->normal);
	comps->over_point = ft_over_point(&comps->point, &comps->normal);
	comps->under_point = ft_under_point(&comps->point, &comps->normal);
	ft_get_refr_ind(comps, intersections, closest);
	ft_get_schlick(comps);
}

// position - The Ray Tracer Challenge p.58
t_vct	ft_ray_point(const t_ray *ray, double t)
{
	t_vct	point;

	point.x = ray->O.x + ray->D.x * t;
	point.y = ray->O.y + ray->D.y * t;
	point.z = ray->O.z + ray->D.z * t;
	point.w = 1;
	return (point);
}

// reflect - The Ray Tracer Challenge p.83
t_vct	ft_reflect(const t_vct *in, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, 2 * ft_vct_dot(in, normal));
	res = ft_vct_sub(in, &res);
	return (res);
}

// over_point - The Ray Tracer Challenge p.115
t_vct	ft_over_point(const t_vct *point, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, EPSILON);
	res = ft_vct_add(point, &res);
	return (res);
}

// under_point - The Ray Tracer Challenge p.155
t_vct	ft_under_point(const t_vct *point, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, EPSILON);
	res = ft_vct_sub(point, &res);
	return (res);
}

// Test to get n1 and n2
void ft_get_refr_ind(t_comps *comps, t_void_arr *intersections, t_intersection *closest)
{
	size_t			i;
	t_intersection *curr;
	t_void_arr		containers;

	ft_init_void_arr(&containers);
	i = 0;
	while (i < intersections->i && containers.arr)
	{
		curr = (t_intersection *) intersections->arr[i++];
		if (curr == closest)
		{
			if (containers.i == 0)
				comps->n1 = 1;
			else
				comps->n1 = ((t_shape *)containers.arr[containers.i - 1])->refractive;
		}

		if (ft_containers_include(&containers, curr->shape))
			ft_remove_container(&containers, curr);
		else
			ft_void_arr_add(&containers, curr->shape);

		if (curr == closest)
		{
			if (containers.i == 0)
				comps->n2 = 1;
			else
				comps->n2 = ((t_shape *)containers.arr[containers.i - 1])->refractive;
			break ;
		}
	}
	free(containers.arr);
}

int	ft_containers_include(t_void_arr *containers, t_shape *shape)
{
	size_t i;

	i = 0;
	while (i < containers->i)
	{
		if (shape == (t_shape *) containers->arr[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_remove_container(t_void_arr *containers, t_intersection *curr)
{
	size_t	reader;
	size_t	writer;
	t_intersection *intr;

	if (!containers->arr)
		return ;
	reader = 0;
	writer = 0;
	while (reader < containers->i)
	{
		intr = (t_intersection *) containers->arr[reader];
		if (curr != intr)
			containers->arr[writer++] = containers->arr[reader];
		reader++;
	}
	containers->i -= 1;
}

void	ft_get_schlick(t_comps *comps)
{
	double cos = ft_vct_dot(&comps->eye, &comps->normal);
	if (comps->n1 > comps->n2)
	{
		double n = comps->n1 / comps->n2;
		double sin2_t = pow(n, 2) * (1 - pow(cos, 2));
		if (sin2_t > 1)
		{
			comps->schlick = 1;
			return ;
		}
		double cos_t = sqrt(1 - sin2_t);
		cos = cos_t;
	}
	double r0 = pow((comps->n1 - comps->n2) / (comps->n1 + comps->n2), 2);
	comps->schlick = r0 + (1 - r0) * pow(1 - cos, 5);
}
