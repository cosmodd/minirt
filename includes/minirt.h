/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:30:22 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/21 11:00:44 by pforesti         ###   ########.fr       */
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
# include "logging.h"
# include "utils.h"

// CONSTANTS
# define WIN_WIDTH		(400)
# define WIN_HEIGHT		(400)
# define FOV			120
# define THRESHOLD		1e-6
# define VOID_COLOR		0x000000

typedef struct s_engine
{
	void	*mlx;
	void	*win;
	t_image	frame;
	t_scene	scene;
	double	vw;
	double	vh;
	double	vp_dist;
}	t_engine;

typedef struct s_hit
{
	t_vec3	raydir;
	t_vec3	normal;
	t_vec3	point;
	t_vec3	color;
	double	t;
}	t_hit;

void	quit(t_engine *engine);

// RAYTRACING
void	basic_raytracer(t_engine *engine);
void	raytrace(t_scene scene, t_hit *hit);

// SCENE PARSING
bool	parse_scene(t_engine *engine, char *path);

#endif
