/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/24 16:20:10 by mrattez          ###   ########.fr       */
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
	t_hit	hit;
	double	color;
	int		x;
	int		y;

	hit = (t_hit){0};
	hit.pos = engine->scene.camera.position;
	y = -WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT / 2)
	{
		x = -WIN_WIDTH / 2;
		while (x < WIN_WIDTH / 2)
		{
			hit.raydir = generate_raydir(engine, (t_vec2){x, y});
			hit.raydir = vec3_mat4(hit.raydir, engine->scene.camera.view);
			raytrace(engine->scene, &hit);
			put_pixel_canvas(engine->frame, x, y, vec3_to_rgba(hit.color));
			x++;
		}
		y++;
	}
}
