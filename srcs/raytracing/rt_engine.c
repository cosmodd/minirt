/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/27 13:50:45 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Determine which square on
 * the viewport corresponds to the canvas pixel.
 *
 * @param c Canvas pixel
 * @return t_vec3f
 */
static t_vec3	canvas_to_viewport(t_engine *engine, int x, int y)
{
	t_vec3	v;

	v.x = x * ((float)engine->vw / (float)WIN_WIDTH);
	v.y = y * ((float)engine->vh / (float)WIN_HEIGHT);
	v.z = engine->vp_dist;
	return (v);
}

void	basic_raytracer(t_engine *engine)
{
	for (int x = -WIN_WIDTH / 2; x < WIN_WIDTH / 2; x++)
	{
		for (int y = -WIN_HEIGHT / 2; y < WIN_HEIGHT / 2; y++)
		{
			t_vec3 raydir = canvas_to_viewport(engine, x, y);
			int color = raytrace(engine->scene, raydir);
			put_pixel_canvas(engine->frame, x, y, color);
		}
	}
}

