/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:33:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/12 20:25:41 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PATTERNS_H
# define PATTERNS_H

void	ft_get_uv(double *uv, t_vct *p, t_obj *obj);
void	ft_spherical_map(double *uv, t_vct *p);
void	ft_planar_map(double *uv, t_vct *p);
void	ft_cylindrical_map(double *uv, t_vct *p);
void	ft_conical_map(double *uv, t_vct *p);


t_ptrn	ft_ptrn(t_clr (f)(double *uv, double w, double h), double w, double h);
t_clr	ft_checkers(double *uv, double width, double height);

void	ft_texture_and_bump(t_comps *comps, t_obj *obj, t_vct obj_point);
double	ft_grscl(t_clr clr);

#endif
