/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/24 17:12:37 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_vct	ft_reflect(const t_vct *in, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, 2 * ft_vct_dot(in, normal));
	res = ft_vct_sub(in, &res);
	return (res);
}

t_vct	ft_sphere_normal(const t_shape *shape, const t_vct *world_point)
{
	t_vct	shape_point;
	t_vct	world_normal;
	
	ft_vct_mtrx_mult(&shape_point, &shape->world_to_shape, world_point);
	ft_vct_mtrx_mult(&world_normal, &shape->normal_to_world, &shape_point);
	ft_vct_norm(&world_normal);
	return (world_normal);
}

t_vct	ft_shape_normal(const t_shape *shape, const t_vct *world_point)
{
	if (shape->type == t_sphere)
		return (ft_sphere_normal(shape, world_point));


	return (ft_create_vct(0,0,0));
}

t_vct	ft_ray_point(const t_ray *ray, float t)
{
	t_vct	position;

	position.x = ray->O.x + ray->D.x * t;
	position.y = ray->O.y + ray->D.y * t;
	position.z = ray->O.z + ray->D.z * t;
	position.w = 1;
	return (position);
}

// over_point - The Ray Tracer Challenge p.115
t_vct	ft_over_point(const t_vct *point, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, EPSILON);
	res = ft_vct_add(point, &res);
	return (res);
}

// prepare_computations - The Ray Tracer Challenge p.76 p.93
void	ft_prepare_computations(t_comps *comps, t_intersection *closest, const t_ray *ray)
{
	comps->t = closest->t;
	comps->shape = closest->shape;
	comps->point = ft_ray_point(ray, comps->t); 
	comps->eye = ft_vct_neg(&ray->D);
	comps->eye.w = 0;
	comps->normal = ft_shape_normal(comps->shape, &comps->point);
	comps->inside = 0;
	if (ft_vct_dot(&comps->normal, &comps->eye) < 0)
	{
		comps->inside = 1;
		comps->normal = ft_vct_neg(&comps->normal);
	}
	comps->reflect = ft_reflect(&ray->D, &comps->normal);
	comps->over_point = ft_over_point(&comps->point, &comps->normal);
}



t_intersection	*ft_closest_intersection(t_void_arr *intersections)
{
	t_intersection	*current;
	t_intersection	*closest;
	float			lowest_time;
	size_t			i;

	if (!intersections->arr)
		return (NULL);
	lowest_time = FLT_MAX;
	i = 0;
	closest = NULL;
	while (i < intersections->i)
	{
		current = (t_intersection *) intersections->arr[i];
		if (0 <= current->t && current->t < lowest_time)
		{
			lowest_time = current->t;
			closest = current;
		}
		i++;
	}
	return (closest);
}

t_clr	ft_get_color(const t_ray *ray, t_scene *scene, int recursion_depth, t_void_arr *intersections)
{
	t_comps			comps;
	(void)			scene;
	(void)			recursion_depth;
	t_intersection	*closest;
	//t_clr			surface_color;
	size_t			i;
	t_light			*light;


	closest = ft_closest_intersection(intersections);

	if (!closest)
    	return (ft_create_clr(0, 0, 0));
	ft_prepare_computations(&comps, closest, ray);
	i = 0;
	while (i < scene->lights.i)
	{
		light = (t_light *) scene->lights.arr[i++];
		//surface_color = ft_lighting(&comps, scene, light);
	}
	(void) light;
	

	return closest->shape->color;
}

/*t_clr	ft_lighting(t_comps *comps, t_scene *scene, t_light *light)
{
	t_clr	res;
	t_clr	shape_color;

	shape_color = comps->shape->color;
	res = ft_ambient
}*/
/*
	// Light
	t_vct P = ft_vct_add(O, ft_vct_sclr_mult(D, t_closest));
	t_vct N = ft_vct_sub(P, shape_closest->position);
	N = ft_vct_sclr_div(N, ft_vct_len(N));
	if (shape_closest->type == t_plane)
	{
		N = shape_closest->orientation;
		N = ft_vct_sclr_div(N, ft_vct_len(N));
	}

	local_color = ft_light(shape_closest->color, scene, P, N, ft_vct_neg(D), shape_closest->specular);

	// Reflected color
	rfl = shape_closest->reflective;
	if (!recursion_depth || rfl <= 0)
		return (local_color);

	float		t_closest_refl = FLT_MAX;
	t_shape		*shape_closest_refl = NULL;

	ft_closest_intersection(P, ft_reflect_ray(ft_vct_neg(D), N), scene, t_min, t_max, &t_closest_refl, &shape_closest_refl);
	reflected_color = ft_get_color(P, ft_reflect_ray(ft_vct_neg(D) , N), scene , t_min, t_max, recursion_depth - 1, t_closest_refl, shape_closest_refl);

	local_color.r = local_color.r  * (1 - rfl) + reflected_color.r * rfl;
	local_color.g = local_color.g  * (1 - rfl) + reflected_color.g * rfl;
	local_color.b = local_color.b  * (1 - rfl) + reflected_color.b * rfl;	
	
	return (local_color);
}


t_clr	ft_light(t_clr color, t_scene *scene, t_vct P, t_vct N, t_vct V, float s)
{
	float	light_intensity;
	t_vct	L;
	t_vct	R;
	float	n_dot_l;
	float	r_dot_v;
	t_light	*light;
	size_t	i;

	light_intensity = 0;
	i = 0;
	while (i < scene->lights.i)
	{
		light = scene->lights.arr[i++];

		if (light->type == t_ambient)
		{
			light_intensity += light->intensity;
			continue ;
		}
		if (light->type == t_point)
			L = ft_vct_sub(light->position, P);
		else
			L = light->direction;
		
		// Shadow
		float		t_shdw_closest = FLT_MAX;
		t_shape		*shdw_closest = NULL;

		ft_closest_intersection(P, L, scene, 0.001, 10000, &t_shdw_closest, &shdw_closest);
		if (shdw_closest)
			continue ;

		// Diffuse
		n_dot_l = ft_vct_dot(N, L);
		if (n_dot_l > 0)
			light_intensity += light->intensity * n_dot_l / (ft_vct_len(N) * ft_vct_len(L));
		
		// Specular
		if (s != -1)
		{
			R = ft_vct_sub(ft_vct_sclr_mult(N, 2 * n_dot_l), L);
			r_dot_v = ft_vct_dot(R, V);
			if (r_dot_v > 0)
				light_intensity += light->intensity * pow(r_dot_v / (ft_vct_len(R) * ft_vct_len(V)), s);
		}
	}
	
	color.r = ft_modify_channel(color.r, light_intensity);
	color.g = ft_modify_channel(color.g, light_intensity);
	color.b = ft_modify_channel(color.b, light_intensity);
	return (color);
}
*/

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	ft_clr_to_int(t_clr clr)
{
    return (ft_pixel(clr.r, clr.g, clr.b, 255));
}

t_clr	ft_create_clr(float r, float g, float b)
{
	t_clr	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

float	ft_modify_channel(float ch, float i)
{
	ch = ch * i;
	if (ch < 0)
		return (0);
	if (ch > 255)
		return (255);
	return (ch);
}



