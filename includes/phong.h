/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:13:02 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/04 15:03:09 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHONG_H
# define PHONG_H

t_clr	ft_phong(t_clr_recur *rec);
t_clr	ft_ambient(t_clr_recur *rec);
t_clr	ft_diffuse(t_phong *ph, t_clr_recur *rec);
t_clr	ft_specular(t_phong *ph, t_clr_recur *rec);
int		ft_shadow(t_clr_recur *rec);

#endif
