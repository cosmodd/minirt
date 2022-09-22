/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:21:45 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 14:08:25 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}				t_vec3;

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




t_vec3f	v3f_normalize(t_vec3f a);
t_vec3f	v3f_plus_v3f(t_vec3f a, t_vec3f b);
double	v3f_module(t_vec3f a);
t_vec3f	v3f_minus_v3f(t_vec3f a, t_vec3f b);
double	v3f_dot_v3f(t_vec3f a, t_vec3f b);
t_vec3f	v3f_scale(t_vec3f a, double b);
t_vec3f	v3f_minus(t_vec3f a, double b);
t_vec3f	v3f_affect(double x, double y, double z);
t_vec3	v3_scale(t_vec3 a, double b);

#endif