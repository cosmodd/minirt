/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:30:22 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/14 13:09:37 by pforesti         ###   ########.fr       */
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
# define WIN_WIDTH		(1280)
# define WIN_HEIGHT		(760)
# define FOV			120
# define INF			1e6

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

void	quit(t_engine *engine);

// RAYTRACING
void	basic_raytracer(t_engine *engine);
int		raytrace(t_scene scene, t_vec3 raydir);

// SCENE PARSING
bool	parse_scene(t_engine *engine, char *path);

#endif
