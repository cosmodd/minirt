/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:48:50 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 10:26:43 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "minirt.h"

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


#endif