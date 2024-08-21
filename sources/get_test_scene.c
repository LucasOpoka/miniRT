/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_test_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:47:38 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/21 15:28:33 by lucas            ###   ########.fr       */
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
	shape1->position = ft_create_vct(0, -1, 3); // CENTER
	shape1->radius = 1;
	shape1->color = ft_create_clr(255, 0, 0); // RED
	shape1->specular = 500;
	shape1->reflective = 0.2;
	shape1->scale = ft_create_vct(2, 1, 1);
	shape1->orientation = ft_create_vct(1, 0, 0);

	t_shape *shape2 = malloc(sizeof(t_shape));
	shape2->type = t_sphere;
	shape2->position = ft_create_vct(2, 0, 4); //ON THE RIGHT
	shape2->radius = 1;
	shape2->color = ft_create_clr(0, 0, 255); //BLUE
	shape2->specular = 500;
	shape2->reflective = 0.3;
	shape2->scale = ft_create_vct(2, 1, 1);
	shape2->orientation = ft_create_vct(1, 0, 0);

	t_shape *shape3 = malloc(sizeof(t_shape));
	shape3->type = t_sphere;
	shape3->position = ft_create_vct(-2, 0, 4); //ON THE LEFT
	shape3->radius = 1;
	shape3->color = ft_create_clr(0, 255, 0); // GREEN
	shape3->specular = 10;
	shape3->reflective = 0.4;
	shape3->scale = ft_create_vct(2, 1, 1);
	shape3->orientation = ft_create_vct(1, 0, 0);

	t_shape *shape4 = malloc(sizeof(t_shape));
	shape4->type = t_sphere;
	shape4->position = ft_create_vct(0, -5001, 0); //BIG AT BOTTOM
	shape4->radius = 5000;
	shape4->color = ft_create_clr(255, 255, 0); // YELLOW
	shape4->specular = 1000;
	shape4->reflective = 0.5;
	shape4->scale = ft_create_vct(1, 1, 1);
	shape4->orientation = ft_create_vct(0, 0, 1);

	t_shape *shape5 = malloc(sizeof(t_shape));
	shape5->type = t_plane;
	shape5->position = ft_create_vct(0, 0, 5);
	shape5->color = ft_create_clr(90, 34, 139);
	shape5->orientation = ft_create_vct(0, 1, -1);
	shape5->specular = 1000;
	shape5->reflective = 0.4;
	shape5->scale = ft_create_vct(1, 1, 1);
	shape5->orientation = ft_create_vct(0, 0, 0);
	
	ft_void_arr_add(&scene.shapes, shape1);
	ft_void_arr_add(&scene.shapes, shape2);
	ft_void_arr_add(&scene.shapes, shape3);
	ft_void_arr_add(&scene.shapes, shape4);
	//ft_void_arr_add(&scene.shapes, shape5);

	// Lights
	ft_init_void_arr(&scene.lights);

	t_light *light1 = malloc(sizeof(t_light));
	light1->type = t_ambient;
	light1->intensity = 0.2;

	t_light *light2 = malloc(sizeof(t_light));
	light2->type = t_point;
	light2->intensity = 0.6;
	light2->position = ft_create_vct(2, 1, 0);
	
	t_light *light3 = malloc(sizeof(t_light));
	light3->type = t_directional;
	light3->intensity = 0.2;
	light3->direction = ft_create_vct(1, 4, 4);
	
	ft_void_arr_add(&scene.lights, light1);
	ft_void_arr_add(&scene.lights, light2);
	ft_void_arr_add(&scene.lights, light3);

	return (scene);
}
