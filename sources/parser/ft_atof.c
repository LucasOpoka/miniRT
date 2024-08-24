/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:33 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:07:34 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

double ft_atof(const char *s)
{
	const char	*str = s;
	double		a = 0.0;
	int			e = 0;

	if (*s == '-')
		s++;
	while (*s && ft_isdigit(*s))
		a = a*10.0 + (*s++ - '0');
	if (*s == '.')
		s++;
	while (*s && ft_isdigit(*s))
	{
		a = a*10.0 + (*s++ - '0');
		e = e-1;
	}
	while (e < 0)
	{
		a *= 0.1;
		e++;
	}
	if (*str == '-')
		a *= -1.0;
	return a;
}

