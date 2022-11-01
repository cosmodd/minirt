/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:30:22 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/01 15:41:02 by mrattez          ###   ########.fr       */
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
# include "mlx_keycodes.h"
# include "maths.h"
# include "objects.h"
# include "logging.h"
# include "utils.h"

// CONSTANTS
# define WIN_WIDTH		(400)
# define WIN_HEIGHT		(400)
# define FOV			120
# define THRESHOLD		1e-6
# define VOID_COLOR		0x87ceeb
# define REC_LIMIT		1

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

int		quit(t_engine *engine);

// RAYTRACING
void	ray(t_hit *hit, t_scene *scene, t_collideable *o_p, size_t rec_limit);
void	basic_raytracer(t_engine *engine);
void	raytrace(t_scene scene, t_hit *hit, size_t rec_limit);
void	compute_lighting(t_scene scene, t_hit *hit);
bool	in_shadow(t_vec3 point, t_light light, t_scene scene, t_collideable *o_p);

// SCENE PARSING
bool	parse_scene(t_engine *engine, char *path);

#endif
