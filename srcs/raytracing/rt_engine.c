/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/25 02:49:48 by pforesti         ###   ########.fr       */
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
static t_vec3	canvas_to_viewport(int x, int y)
{
	t_vec3	v;

	v.x = x * ((float)VIEWPORT_WIDTH / (float)WIN_WIDTH);
	v.y = y * ((float)VIEWPORT_HEIGHT / (float)WIN_HEIGHT);
	v.z = CAMERA_DISTANCE;
	return (v);
}

void	basic_raytracer(t_image frame)
{
	t_scene	scene;
	t_vec3	camera;

	camera = (t_vec3){0, 0, -5};
	scene.spheres[0].center = (t_vec3){1, 1, 0};
	scene.spheres[0].radius = 1;
	scene.spheres[0].color = (t_vec3){254, 74, 73};
	scene.spheres[1].center = (t_vec3){0, 0, 10};
	scene.spheres[1].radius = 1;
	scene.spheres[1].color = (t_vec3){254, 215, 102};
	scene.spheres[2].center = (t_vec3){-5, 5, 20};
	scene.spheres[2].radius = 1;
	scene.spheres[2].color = (t_vec3){0, 159, 189};
	scene.spheres[3].center = (t_vec3){0, -5001, 0};
	scene.spheres[3].radius = 5000;
	scene.spheres[3].color = (t_vec3){243, 232, 238};

	scene.l_a.intensity = 0.;
	scene.l_p[0].intensity = 1;
	scene.l_p[0].pos = (t_vec3){10, 100, 0};
	scene.l_p[1].intensity = 1;
	scene.l_p[1].pos = (t_vec3){-10, -30, 0};

	for (int x = -WIN_WIDTH / 2; x < WIN_WIDTH / 2; x++)
	{
		for (int y = -WIN_HEIGHT / 2; y < WIN_HEIGHT / 2; y++)
		{
			t_vec3 D = canvas_to_viewport(x, y);
			int color = rays_trace(camera, D, 1, INF, scene);
			put_pixel_canvas(frame, x, y, color);
		}
	}
}

