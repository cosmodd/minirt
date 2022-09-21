/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:21:45 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 10:27:06 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

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

#endif