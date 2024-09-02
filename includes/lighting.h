/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:13:02 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 18:53:50 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIGHTING_H
# define LIGHTING_H

t_clr	ft_lighting(t_comps *comps, t_scene *scene, t_light *light,
			t_clr *ambient);
t_clr	ft_get_ambient(t_ambient *ambient, t_clr *obj_color);

#endif
