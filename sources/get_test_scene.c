/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_test_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:47:38 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 15:09:12 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_scene	get_test_scene(void)
{
	// Test scene
	t_scene scene;

	//Camera
	scene.camera.fov = FOV;

	scene.camera.position.x = 0;
	scene.camera.position.y = 0;
	scene.camera.position.z = -5;
	scene.camera.position.w = 1;

	scene.camera.direction.x = 0;
	scene.camera.direction.y = 0;
	scene.camera.direction.z = 1;
	scene.camera.direction.w = 0;

	// Shapes
	ft_init_void_arr(&scene.shapes);

	t_shape *shape1 = malloc(sizeof(t_shape));
	shape1->type = t_sphere;
	shape1->position = ft_create_vct(0, 0, 0); // CENTER
	shape1->radius = 1;
	shape1->color = ft_create_clr(0, 0, 0); // RED
	shape1->specular = 0.9;
	shape1->diffuse = 0;
	shape1->shininess = 300;
	shape1->reflective = 0.9;
	shape1->refractive = 1.5;
	shape1->transparency = 0.9;
	shape1->scale = ft_create_vct(1, 1, 1);
	shape1->orientation = ft_create_vct(0, 0, 0);

	t_shape *shape2 = malloc(sizeof(t_shape));
	shape2->type = t_sphere;
	shape2->position = ft_create_vct(0, 0, 0); // INSIDE CENTER
	shape2->radius = 0.5;
	shape2->color = ft_create_clr(0, 0, 0); //BLUE
	shape2->specular = 0.9;
	shape2->diffuse = 0;
	shape2->shininess = 300;
	shape2->reflective = 0.9;
	shape2->refractive = 1.0000034;
	shape2->transparency = 0.9;
	shape2->scale = ft_create_vct(1, 1, 1);
	shape2->orientation = ft_create_vct(0, 0, 0);

	t_shape *shape3 = malloc(sizeof(t_shape));
	shape3->type = t_sphere;
	shape3->position = ft_create_vct(-3, -2, 6); //ON THE LEFT
	shape3->radius = 0.5;
	shape3->color = ft_create_clr(0, 0, 0); // GREEN
	shape3->specular = 0.9;
	shape3->diffuse = 0.9;
	shape3->shininess = 500;
	shape3->reflective = 0.5;
	shape3->refractive = 1.5;
	shape3->transparency = 0;
	shape3->scale = ft_create_vct(1, 1, 1);
	shape3->orientation = ft_create_vct(0, 0, 0);

	t_shape *shape4 = malloc(sizeof(t_shape));
	shape4->type = t_sphere;
	shape4->position = ft_create_vct(0, -5001, 0); //BIG AT BOTTOM
	shape4->radius = 1;
	shape4->color = ft_create_clr(255, 255, 0); // YELLOW
	shape4->specular = 0.9;
	shape4->diffuse = 0.9;
	shape4->shininess = 100;
	shape4->reflective = 0.9;
	shape4->refractive = 1.5;
	shape4->transparency = 0;
	shape4->scale = ft_create_vct(5000, 5000, 5000);
	shape4->orientation = ft_create_vct(0, 0, 1);

	t_shape *shape10 = malloc(sizeof(t_shape));
	shape10->type = t_sphere;
	shape10->position = ft_create_vct(0, 0, 5005); //BIG AT BOTTOM
	shape10->radius = 1;
	shape10->color = ft_create_clr(255, 255, 0); // YELLOW
	shape10->specular = 0.9;
	shape10->diffuse = 0.9;
	shape10->shininess = 100;
	shape10->reflective = 0.9;
	shape10->refractive = 1.5;
	shape10->transparency = 0;
	shape10->scale = ft_create_vct(5000, 5000, 5000);
	shape10->orientation = ft_create_vct(0, 0, 1);


	t_shape *back = malloc(sizeof(t_shape));
	back->type = t_plane;
	back->position = ft_create_vct(0, 0, 10); // BACK PLANE
	back->color = ft_create_clr(0, 0, 0);
	back->orientation = ft_create_vct(0, 0, -1);
	back->specular = 0;
	back->diffuse = 0.2;
	back->shininess = 100;
	back->reflective = 0;
	back->refractive = 1;
	back->transparency = 0;
	back->scale = ft_create_vct(1, 1, 1);
	
	t_shape *shape6 = malloc(sizeof(t_shape));
	shape6->type = t_cylinder;
	shape6->position = ft_create_vct(-3, 0, 2); //CYLINDER
	shape6->color = ft_create_clr(150, 100, 75);
	shape6->orientation = ft_create_vct(0, 0, 1);
	shape6->specular = 0.9;
	shape6->shininess = 100;
	shape6->reflective = 0.2;
	shape6->refractive = 1.5;
	shape6->transparency = 0.5;
	shape6->scale = ft_create_vct(1, 1, 1);
	shape6->orientation = ft_create_vct(0, 0, 0);
	shape6->height = 3;

	t_shape *shape7 = malloc(sizeof(t_shape));
	shape7->type = t_plane;
	shape7->position = ft_create_vct(0, -4, 0); //PURPLE PLANE
	shape7->color = ft_create_clr(0, 70, 139);
	shape7->orientation = ft_create_vct(0, 1, 0);
	shape7->specular = 0.9;
	shape7->shininess = 100;
	shape7->reflective = 0;
	shape7->refractive = 1.5;
	shape7->transparency = 0;
	shape7->scale = ft_create_vct(1, 1, 1);

	t_shape *r = malloc(sizeof(t_shape));
	r->type = t_plane;
	r->position = ft_create_vct(4, 0, 0); //PURPLE PLANE
	r->color = ft_create_clr(255, 0, 255);
	r->orientation = ft_create_vct(-1, 0, 0);
	r->specular = 0.9;
	r->shininess = 100;
	r->reflective = 0;
	r->refractive = 1.5;
	r->transparency = 0;
	r->scale = ft_create_vct(1, 1, 1);

	t_shape *l = malloc(sizeof(t_shape));
	l->type = t_plane;
	l->position = ft_create_vct(-4, 0, 0); //RED LEFT PLANE
	l->color = ft_create_clr(255, 0, 0);
	l->orientation = ft_create_vct(1, 0, 0);
	l->specular = 0.9;
	l->shininess = 100;
	l->reflective = 0;
	l->refractive = 1.5;
	l->transparency = 0;
	l->scale = ft_create_vct(1, 1, 1);

	t_shape *up = malloc(sizeof(t_shape));
	up->type = t_plane;
	up->position = ft_create_vct(0, 4, 0); //GREEN UP PLANE
	up->color = ft_create_clr(0, 255, 0);
	up->orientation = ft_create_vct(0, -1, 0);
	up->specular = 0.9;
	up->shininess = 100;
	up->reflective = 0;
	up->refractive = 1.5;
	up->transparency = 0;
	up->scale = ft_create_vct(1, 1, 1);

	t_shape *front = malloc(sizeof(t_shape));
	front->type = t_plane;
	front->position = ft_create_vct(0, 0, -6); //BACK PLANE
	front->color = ft_create_clr(255, 255, 0);
	front->orientation = ft_create_vct(0, 0, 1);
	front->specular = 0.9;
	front->shininess = 100;
	front->reflective = 0;
	front->refractive = 1.5;
	front->transparency = 0;
	front->scale = ft_create_vct(1, 1, 1);

	
	ft_void_arr_add(&scene.shapes, shape1);
	ft_void_arr_add(&scene.shapes, shape2);
	//ft_void_arr_add(&scene.shapes, shape3);
	//ft_void_arr_add(&scene.shapes, shape4);
	//ft_void_arr_add(&scene.shapes, shape10);
	//ft_void_arr_add(&scene.shapes, shape6);
	//ft_void_arr_add(&scene.shapes, shape7);
	ft_void_arr_add(&scene.shapes, back);
	//ft_void_arr_add(&scene.shapes, r);
	//ft_void_arr_add(&scene.shapes, l);
	//ft_void_arr_add(&scene.shapes, up);
	//ft_void_arr_add(&scene.shapes, front);

	// Lights
	ft_init_void_arr(&scene.lights);

	scene.ambient.intensity = 0.5;
	scene.ambient.color = ft_create_clr(255, 255, 255);

	t_light *light2 = malloc(sizeof(t_light));
	light2->type = t_point;
	light2->intensity = 0.5;
	light2->position = ft_create_vct(2, 10, -5);
	light2->direction = ft_create_vct(1, -1, 0);
	light2->color = ft_create_clr(255, 255, 255);
	
	t_light *light3 = malloc(sizeof(t_light));
	light3->type = t_directional;
	light3->intensity = 0.2;
	light3->position = ft_create_vct(1, 3, 3);
	light3->direction = ft_create_vct(-1, 1, 0);
	light3->color = ft_create_clr(255, 255, 255);
	
	ft_void_arr_add(&scene.lights, light2);
	//ft_void_arr_add(&scene.lights, light3);

	return (scene);
}
