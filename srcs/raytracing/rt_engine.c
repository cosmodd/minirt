/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/19 09:36:21 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Generates a direction vector from pixel coordinates.
 *
 * @param engine Data of the entire engine.
 * @param pixel Coordinates of the pixel to convert.
 * @return t_vec3 - Direction vector
 */
static t_vec3	generate_raydir(t_engine *engine, t_vec2 pixel)
{
	t_vec3	v;

	v.x = (pixel.x / (double)WIN_WIDTH) * engine->vw;
	v.y = (pixel.y / (double)WIN_HEIGHT) * engine->vh;
	v.z = -engine->vp_dist;
	return (vec3_normalize(v));
}

void	basic_raytracer(t_engine *engine)
{
	t_vec3	raydir;
	int		color;
	int		x;
	int		y;

	y = -WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT / 2)
	{
		x = -WIN_WIDTH / 2;
		while (x < WIN_WIDTH / 2)
		{
			raydir = generate_raydir(engine, (t_vec2){x, y});
			raydir = vec3_mat4(raydir, engine->scene.camera.view);
			color = raytrace(engine->scene, raydir);
			put_pixel_canvas(engine->frame, x, y, color);
			x++;
		}
		y++;
	}
}
