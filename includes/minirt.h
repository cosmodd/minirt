/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:30:22 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/25 02:48:30 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// STANDARD
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

// LIBRARIES
# include "mlx.h"
# include "libft.h"

// OTHERS
# include "xutils.h"
# include "keys.h"
# include "maths.h"
# include "objects.h"

// CONSTANTS
# define WIN_WIDTH			1000
# define WIN_HEIGHT 		1000
# define VIEWPORT_WIDTH		1
# define VIEWPORT_HEIGHT	1
# define CAMERA_DISTANCE	1.5f
# define INF				100000

typedef struct s_engine
{
	void	*mlx;
	void	*win;
	t_image	frame;
}	t_engine;

/* rt_rays.c	*/
int		rays_trace(t_vec3 O, t_vec3 D, int t_min, int t_max, t_scene scene);
t_vec2	rays_intercept_sphere(t_vec3 O, t_vec3 D, t_sphere sphere);

/* rt_engine.c	*/
void	basic_raytracer(t_image	frame);

#endif
