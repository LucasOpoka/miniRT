/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:06:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/23 14:03:26 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <pthread.h>

int			threads_init(t_mrt *mrt, t_scene *scene);
void		threads_wait(t_mrt *mrt);
void		threads_join(t_mrt *mrt);

void	render_image(t_mrt *mrt)
{
	pthread_mutex_lock(&mrt->lock);
	mrt->threads_finished = 0;
	mrt->do_render = 1;
	pthread_cond_broadcast(&mrt->notify);
	pthread_mutex_unlock(&mrt->lock);
	threads_wait(mrt);
}

void	render(t_mrt *mrt, t_scene *scene)
{
	const mlx_image_t	*img = mrt->img;

	ft_bzero(img->pixels, img->width * img->height * sizeof(int));
	mrt->scene = scene;
	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	ft_set_all_objs_matrices(scene);
	render_image(mrt);
}
