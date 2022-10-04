/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:30:22 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/04 15:37:26 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// STANDARD
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>

// LIBRARIES
# include "mlx.h"
# include "libft.h"

// OTHERS
# include "xutils.h"
# include "keys.h"
# include "maths.h"
# include "objects.h"

// CONSTANTS
# define WIN_WIDTH		(900)
# define WIN_HEIGHT		(600)
# define FOV			120
# define INF			100000

typedef struct s_engine
{
	void	*mlx;
	void	*win;
	t_image	frame;
	t_scene	scene;
	double	hfov;
	double	vfov;
	double	vw;
	double	vh;
	double	vp_dist;
}	t_engine;

/* rt_rays.c	*/
int		raytrace(t_scene scene, t_vec3 raydir);

/* rt_engine.c	*/
void	basic_raytracer(t_engine *engine);

#endif
