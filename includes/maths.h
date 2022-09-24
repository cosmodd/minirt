/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:21:45 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 15:59:03 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

#include <math.h>

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
double	vec2_cross(t_vec2 a, t_vec2 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec2_dot(t_vec2 a, t_vec2 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
double	vec2_magnitude(t_vec2 a);
double	vec3_magnitude(t_vec3 a);
t_vec2	vec2_normalize(t_vec2 vec);
t_vec3	vec3_normalize(t_vec3 vec);
t_vec2	vec2_scalar(t_vec2 vec, double scalar);
t_vec3	vec3_scalar(t_vec3 vec, double scalar);
t_vec2	vec2_sub(t_vec2 a, t_vec2 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);

#endif
