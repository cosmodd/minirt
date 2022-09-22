/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:20:54 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 11:17:39 by pforesti         ###   ########.fr       */
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
	scene.spheres[0].center.x = 0;
	scene.spheres[0].center.y = -1;
	scene.spheres[0].center.z = 3;
	scene.spheres[0].radius = 1;
	scene.spheres[0].color = create_trgb(0, 255, 0, 0);
	scene.spheres[1].center.x = -2;
	scene.spheres[1].center.y = 0;
	scene.spheres[1].center.z = 4;
	scene.spheres[1].radius = 1;
	scene.spheres[1].color = create_trgb(0, 0, 255, 0);
	scene.spheres[2].center.x = 2;
	scene.spheres[2].center.y = 0;
	scene.spheres[2].center.z = 4; 
	scene.spheres[2].radius = 1;
	scene.spheres[2].color = create_trgb(0, 0, 0, 255);
	t_vec3f	O = {0, 0, -5};
	
	for	(int x = -WIN_WIDTH / 2 ; x < WIN_WIDTH / 2 ; x++) {
		for (int y = -WIN_HEIGHT / 2 ; y < WIN_HEIGHT / 2; y++) {
			t_vec3f D = canvas_to_viewport(x, y);
			int color = rays_trace(O, D, 1, INF, scene);
			put_pixel_canvas(frame, x, y, color);
		}
	}
}