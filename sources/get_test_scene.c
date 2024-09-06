/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_test_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:47:38 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/06 14:07:59 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_scene	get_test_scene(void)
{
	// Test scene
	t_scene scene;

	//Camera
	scene.cam.fov = FOV;
	scene.cam.pos = ft_create_point(0, 0, -5);
	scene.cam.dir = ft_create_vct(0, 0, 1);

	// Shapes
	ft_init_void_arr(&scene.objs);

	t_obj *obj1 = malloc(sizeof(t_obj));
	obj1->type = t_sphere;
	obj1->pos = ft_create_point(0, 0, 0); // CENTER
	obj1->radius = 1;
	obj1->color = ft_create_clr(0, 0, 0); // RED
	obj1->specular = 0.9;
	obj1->diffuse = 0;
	obj1->shininess = 300;
	obj1->reflective = 0;
	obj1->refractive = 1.5;
	obj1->transparency = 0;
	obj1->scale = ft_create_vct(1, 1, 1);
	obj1->orientation = ft_create_vct(0, 0, 0);

	t_obj *air_bubble = malloc(sizeof(t_obj));
	air_bubble->type = t_sphere;
	air_bubble->pos = ft_create_point(0, 0, 0); // INSIDE CENTER
	air_bubble->radius = 0.5;
	air_bubble->color = ft_create_clr(0, 0, 0); //BLUE
	air_bubble->specular = 0.9;
	air_bubble->diffuse = 0;
	air_bubble->shininess = 300;
	air_bubble->reflective = 0.9;
	air_bubble->refractive = 1.0000034;
	air_bubble->transparency = 0.9;
	air_bubble->scale = ft_create_vct(1, 1, 1);
	air_bubble->orientation = ft_create_vct(0, 0, 0);

	t_obj *obj3 = malloc(sizeof(t_obj));
	obj3->type = t_sphere;
	obj3->pos = ft_create_point(-2, 0, 0); //ON THE LEFT
	obj3->radius = 0.5;
	obj3->color = ft_create_clr(0, 255, 0); // GREEN
	obj3->specular = 0.9;
	obj3->diffuse = 0.9;
	obj3->shininess = 500;
	obj3->reflective = 0.5;
	obj3->refractive = 1.5;
	obj3->transparency = 0;
	obj3->scale = ft_create_vct(1, 1, 1);
	obj3->orientation = ft_create_vct(0, 0, 0);

	t_obj *obj4 = malloc(sizeof(t_obj));
	obj4->type = t_sphere;
	obj4->pos = ft_create_point(0, -5001, 0); //BIG AT BOTTOM
	obj4->radius = 1;
	obj4->color = ft_create_clr(255, 255, 0); // YELLOW
	obj4->specular = 0.9;
	obj4->diffuse = 0.9;
	obj4->shininess = 100;
	obj4->reflective = 0.9;
	obj4->refractive = 1.5;
	obj4->transparency = 0;
	obj4->scale = ft_create_vct(5000, 5000, 5000);
	obj4->orientation = ft_create_vct(0, 0, 1);

	t_obj *obj10 = malloc(sizeof(t_obj));
	obj10->type = t_sphere;
	obj10->pos = ft_create_point(0, 0, 5005); //BIG AT BOTTOM
	obj10->radius = 1;
	obj10->color = ft_create_clr(255, 255, 0); // YELLOW
	obj10->specular = 0.9;
	obj10->diffuse = 0.9;
	obj10->shininess = 100;
	obj10->reflective = 0.9;
	obj10->refractive = 1.5;
	obj10->transparency = 0;
	obj10->scale = ft_create_vct(5000, 5000, 5000);
	obj10->orientation = ft_create_vct(0, 0, 1);
	
	t_obj *obj7 = malloc(sizeof(t_obj));
	obj7->type = t_plane;
	obj7->pos = ft_create_point(0, -4, 0); //PURPLE PLANE
	obj7->color = ft_create_clr(0, 70, 139);
	obj7->orientation = ft_create_vct(0, 1, 0);
	obj7->specular = 0.9;
	obj7->shininess = 100;
	obj7->reflective = 0;
	obj7->refractive = 1.5;
	obj7->transparency = 0;
	obj7->scale = ft_create_vct(1, 1, 1);

	t_obj *r = malloc(sizeof(t_obj));
	r->type = t_plane;
	r->pos = ft_create_point(4, 0, 0); //PURPLE PLANE
	r->color = ft_create_clr(255, 0, 255);
	r->orientation = ft_create_vct(-1, 0, 0);
	r->specular = 0.9;
	r->shininess = 100;
	r->reflective = 0;
	r->refractive = 1.5;
	r->transparency = 0;
	r->scale = ft_create_vct(1, 1, 1);

	t_obj *l = malloc(sizeof(t_obj));
	l->type = t_plane;
	l->pos = ft_create_point(-4, 0, 0); //RED LEFT PLANE
	l->color = ft_create_clr(255, 0, 0);
	l->orientation = ft_create_vct(1, 0, 0);
	l->specular = 0.9;
	l->shininess = 100;
	l->reflective = 0;
	l->refractive = 1.5;
	l->transparency = 0;
	l->scale = ft_create_vct(1, 1, 1);

	t_obj *up = malloc(sizeof(t_obj));
	up->type = t_plane;
	up->pos = ft_create_point(0, 4, 0); //GREEN UP PLANE
	up->color = ft_create_clr(0, 255, 0);
	up->orientation = ft_create_vct(0, -1, 0);
	up->specular = 0.9;
	up->shininess = 100;
	up->reflective = 0;
	up->refractive = 1.5;
	up->transparency = 0;
	up->scale = ft_create_vct(1, 1, 1);

	t_obj *front = malloc(sizeof(t_obj));
	front->type = t_plane;
	front->pos = ft_create_point(0, 0, -10); //FORNT PLANE
	front->color = ft_create_clr(255, 255, 0);
	front->orientation = ft_create_vct(0, 0, 1);
	front->specular = 0.9;
	front->shininess = 100;
	front->reflective = 0;
	front->refractive = 1.5;
	front->transparency = 0;
	front->scale = ft_create_vct(1, 1, 1);
	
	t_obj *back = malloc(sizeof(t_obj));
	back->type = t_plane;
	back->pos = ft_create_point(0, 0, 10); // BACK PLANE
	back->color = ft_create_clr(0, 0, 0);
	back->orientation = ft_create_vct(0, 0, -1);
	back->specular = 0;
	back->diffuse = 0.2;
	back->shininess = 100;
	back->reflective = 0;
	back->refractive = 1;
	back->transparency = 0;
	back->scale = ft_create_vct(1, 1, 1);

	t_obj *cylinder = malloc(sizeof(t_obj));
	cylinder->type = t_cylinder;
	cylinder->pos = ft_create_point(0, 0, 2); //CYLINDER
	cylinder->color = ft_create_clr(0, 0, 255);
	cylinder->orientation = ft_create_vct(0, 0, 1);
	cylinder->specular = 0.9;
	cylinder->shininess = 100;
	cylinder->reflective = 0.9;
	cylinder->refractive = 1.5;
	cylinder->radius = 1;
	cylinder->transparency = 0;
	cylinder->scale = ft_create_vct(1, 1, 1);
	cylinder->orientation = ft_create_vct(0, 0, 0);
	cylinder->height = 3;

	// Triangle testing
	t_vct p1 = ft_create_point(-1, 0, 2);
	t_vct p2 = ft_create_point(1, 0, 2);
	t_vct p3 = ft_create_point(0, 1, 2);
	t_vct e1 = ft_vct_sub(&p2, &p1);	
	t_vct e2 = ft_vct_sub(&p3, &p1);

	t_vct normal;
	ft_vct_cross_prod(&normal, &e2, &e1);
	normal.w = 0;
	ft_vct_norm(&normal);

	t_obj *tri = malloc(sizeof(t_obj));
	tri->type = t_triangle;
	tri->color = ft_create_clr(255, 0, 0);
	tri->specular = 0.9;
	tri->shininess = 100;
	tri->reflective = 0.9;
	tri->refractive = 1.5;
	tri->transparency = 0;
	tri->scale = ft_create_vct(1, 1, 1);
	tri->orientation = ft_create_vct(0, 0, 0);
	tri->e1 = e1;
	tri->e2 = e2;
	tri->normal = normal;
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;


	ft_void_arr_add(&scene.objs, obj1);
	//ft_void_arr_add(&scene.objs, air_bubble);
	//ft_void_arr_add(&scene.objs, obj3);
	//ft_void_arr_add(&scene.objs, obj4);
	//ft_void_arr_add(&scene.objs, obj10);
	//ft_void_arr_add(&scene.objs, cylinder);
	//ft_void_arr_add(&scene.objs, obj7);
	ft_void_arr_add(&scene.objs, back);
	//ft_void_arr_add(&scene.objs, r);
	//ft_void_arr_add(&scene.objs, l);
	//ft_void_arr_add(&scene.objs, up);
	//ft_void_arr_add(&scene.objs, front);
	
	//ft_void_arr_add(&scene.objs, tri);

	// Lights
	ft_init_void_arr(&scene.lights);

	scene.ambient.intensity = 0.25;
	scene.ambient.color = ft_create_clr(255, 255, 255);

	t_light *light2 = malloc(sizeof(t_light));
	light2->intensity = 0.25;
	light2->pos = ft_create_vct(2, 10, -5);
	light2->dir = ft_create_vct(1, -1, 0);
	light2->color = ft_create_clr(255, 255, 255);
	
	t_light *light3 = malloc(sizeof(t_light));
	light3->intensity = 0.25;
	light3->pos = ft_create_vct(1, 3, 3);
	light3->dir = ft_create_vct(-1, 1, 0);
	light3->color = ft_create_clr(255, 255, 255);
	
	t_light *light4 = malloc(sizeof(t_light));
	light4->intensity = 0.25;
	light4->pos = ft_create_vct(-2, -2, 2);
	light4->dir = ft_create_vct(1, 1, -1);
	light4->color = ft_create_clr(0, 0, 255);

	
	ft_void_arr_add(&scene.lights, light2);
	ft_void_arr_add(&scene.lights, light3);
	ft_void_arr_add(&scene.lights, light4);

	return (scene);
}
