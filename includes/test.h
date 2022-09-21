/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:48:50 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 08:44:54 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#include "minirt.h"
#define INF	10000

typedef struct s_sphere
{
	t_vec3f	center;
	double	radius;
	int	color;
}				t_sphere;

typedef	struct s_scene
{
	t_sphere	spheres[3];
}				t_scene;

void	basic_raytracer(t_image	frame);

#endif