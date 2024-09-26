/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:41:43 by atorma            #+#    #+#             */
/*   Updated: 2024/09/26 22:44:13 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void		render_image(t_mrt *mrt);

static int	check_bounds(int move_negative, double current_pos)
{
	if (move_negative && current_pos <= -1000)
		return (0);
	if (!move_negative && current_pos >= 1000)
		return (0);
	return (1);
}

static double	move_size(double pos)
{
	double	ret;

	ret = 0.5f;
	if (fabs(pos) < 1)
		return (ret);
	return (fabs(pos) * 0.5f);
}

static int	move_cam_key(mlx_key_data_t k, t_cam *cam)
{
	if (k.key == MLX_KEY_A && check_bounds(1, cam->pos.x))
		cam->pos.x -= move_size(cam->pos.x);
	else if (k.key == MLX_KEY_D && check_bounds(0, cam->pos.x))
		cam->pos.x += move_size(cam->pos.x);
	else if (k.key == MLX_KEY_W && check_bounds(0, cam->pos.z))
		cam->pos.z += move_size(cam->pos.z);
	else if (k.key == MLX_KEY_S && check_bounds(1, cam->pos.z))
		cam->pos.z -= move_size(cam->pos.z);
	else if (k.key == MLX_KEY_SPACE && check_bounds(0, cam->pos.y))
		cam->pos.y += move_size(cam->pos.y);
	else if (k.key == MLX_KEY_LEFT_SHIFT && check_bounds(1, cam->pos.y))
		cam->pos.y -= move_size(cam->pos.y);
	else
		return (0);
	return (1);
}

void	move_camera(mlx_key_data_t k, t_mrt *mrt, t_scene *scene)
{
	if (!move_cam_key(k, &scene->cam))
		return ;
	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	render_image(mrt);
}
