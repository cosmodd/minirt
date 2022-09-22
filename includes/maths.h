/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:21:45 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 12:46:07 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct s_vec2f
{
	double	x;
	double	y;
}				t_vec2f;

typedef struct s_vec3f
{
	double	x;
	double	y;
	double	z;
}				t_vec3f;


double	v3f_dot_v3f(t_vec3f a, t_vec3f b);
t_vec3f	v3f_scale(t_vec3f a, double b);
t_vec3f	v3f_minus(t_vec3f a, double b);
t_vec3f	v3f_affect(double x, double y, double z);

#endif
