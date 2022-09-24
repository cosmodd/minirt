/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:48:50 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 15:56:11 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef struct s_camera
{
	void	*test;
}	t_camera;

/* Lights	*/
/*	- intensity cannot be greater than 1.	*/
typedef struct s_light_ambient
{
	double	intensity;
}	t_light_ambient;

typedef struct s_light_point
{
	double	intensity;
	t_vec3	pos;
}	t_light_point;

/* Objects	*/
typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_vec3	color;
}	t_sphere;

typedef struct s_scene
{
	t_sphere		spheres[4];
	t_light_ambient	l_a;
	t_light_point	l_p[3];
}	t_scene;

#endif
