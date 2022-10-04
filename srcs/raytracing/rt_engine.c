/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/04 15:34:51 by mrattez          ###   ########.fr       */
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
	for (int y = -WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
	{
		for (int x = -WIN_WIDTH / 2; x < WIN_WIDTH; x++)
		{
			t_vec3 raydir = generate_raydir(engine, (t_vec2){x, y});
			raydir = vec3_mat4(raydir, engine->scene.camera.view);
			int color = raytrace(engine->scene, raydir);
			put_pixel_canvas(engine->frame, x, y, color);
		}
	}
}

