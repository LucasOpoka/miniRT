/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:33:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/06 14:35:53 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PATTERNS_H
# define PATTERNS_H

void	ft_spherical_map(double *uv, t_vct *p);
void	ft_planar_map(double *uv, t_vct *p);
t_clr	ft_checkers(double *uv, double width, double height);

#endif
