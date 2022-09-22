/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 14:11:42 by pforesti         ###   ########.fr       */
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
static t_vec3f	canvas_to_viewport(int x, int y)
{
	t_vec3f	v;

	v.x = x * ((float)VIEWPORT_WIDTH / (float)WIN_WIDTH);
	v.y = y * ((float)VIEWPORT_HEIGHT / (float)WIN_HEIGHT);
	v.z = CAMERA_DISTANCE;
	return (v);
}

void	basic_raytracer(t_image	frame)
{
	t_scene	scene;
	scene.spheres[0].center = v3f_affect(0, -1, 1);
	scene.spheres[0].radius = 1;
	scene.spheres[0].color = v3_affect(255, 0, 0);

	scene.spheres[1].center = v3f_affect(-2, 0,2);
	scene.spheres[1].radius = 1;
	scene.spheres[1].color = v3_affect(0, 255, 0);

	scene.spheres[2].center = v3f_affect(2, 0, 2);
	scene.spheres[2].radius = 1;
	scene.spheres[2].color = v3_affect(0, 0, 255);

	scene.spheres[3].center = v3f_affect(0, -5001, 0);
	scene.spheres[3].radius = 5000;
	scene.spheres[3].color = v3_affect(255, 255, 0);


	scene.l_a.intensity = 0.2;
	scene.l_p[0].intensity = 0.9;
	scene.l_p[0].pos = v3f_affect(5, 5, 0);

	t_vec3f	O = {0, 0, -5};

	for	(int x = -WIN_WIDTH / 2 ; x < WIN_WIDTH / 2 ; x++) {
		for (int y = -WIN_HEIGHT / 2 ; y < WIN_HEIGHT / 2; y++) {
			t_vec3f D = canvas_to_viewport(x, y);
			int color = rays_trace(O, D, 1, INF, scene);
			put_pixel_canvas(frame, x, y, color);
		}
	}
}
