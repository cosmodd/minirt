/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 09:39:16 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# include "test.h"

t_scene	g_scene;

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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

/**
 * @brief Find if a ray intercept a sphere.\n
 * Quadratic equation obtained from : the equation for 
 * all points on a sphere && the equation from all points on
 * a ray.
 * 
 * @param O Origin of the ray (camera).
 * @param D Direction of the ray (viewport square).
 * @param sphere 
 * @return t_vec2f 
 */
t_vec2f	rays_intercept_sphere(t_vec3f O, t_vec3f D, t_sphere sphere)
{
	t_vec2f	t;

	double	r = sphere.radius;
	t_vec3f	CO = {O.x - sphere.center.x, O.y - sphere.center.y, O.z - sphere.center.z};

	double	a = v3f_dot_v3f(D, D);
	double	b = 2 * v3f_dot_v3f(CO, D);
	double	c = v3f_dot_v3f(CO, CO) -  r*r;

	double discriminant = b*b - 4*a*c;
	if (discriminant <= 0) {
		t.x = INF;	
		t.y = INF;	
	}
	else {
		t.x = (-b + sqrt(discriminant)) / (2 * a);
		t.y = (-b - sqrt(discriminant)) / (2 * a);
	}
	return (t);
}

/**
 * @brief Compute rays from Origin to given Direction. 
 * Return the color of intercepted object - if there is any.
 * P = O + t(D - O)
 * @param O Origin of the ray(camera).
 * @param D Direction of the ray(viewport square)
 * @param t_min Minimum t scalar.
 * @param t_max Maximum t scalar (in facts its infinite..)
 * @return int 
 */
int	rays_trace(t_vec3f O, t_vec3f D, int t_min, int t_max)
{
	int			closest_t = INF;
	t_sphere*	closest_sphere = NULL;

	for (int i = 0 ; i < 3 ; i++) { 
		t_vec2f	t = rays_intercept_sphere(O, D, g_scene.spheres[i]);
		if (t.x >= t_min && t.x <= t_max && t.x < closest_t) {
			closest_t = t.x;
			closest_sphere = &g_scene.spheres[i];
		}
		if (t.y >= t_min && t.y <= t_max && t.y < closest_t) {
			closest_t = t.y;
			closest_sphere = &g_scene.spheres[i];
		}
	}
	if (closest_sphere == NULL)
		return (create_trgb(0, 0, 0, 0));
	return (closest_sphere->color);
}

void	basic_raytracer(t_image	frame)
{
	g_scene.spheres[0].center.x = 0;
	g_scene.spheres[0].center.y = 0;
	g_scene.spheres[0].center.z = 3;
	g_scene.spheres[0].radius = 1;
	g_scene.spheres[0].color = create_trgb(0, 255, 0, 0);
	g_scene.spheres[1].center.x = -1;
	g_scene.spheres[1].center.y = 0;
	g_scene.spheres[1].center.z = 5;
	g_scene.spheres[1].radius = 1;
	g_scene.spheres[1].color = create_trgb(0, 0, 255, 0);
	g_scene.spheres[2].center.x = 1;
	g_scene.spheres[2].center.y = 0;
	g_scene.spheres[2].center.z = 1; 
	g_scene.spheres[2].radius = 1;
	g_scene.spheres[2].color = create_trgb(0, 0, 0, 255);
	t_vec3f	O = {0, 0, 0};
	
	for	(int x = -WIN_WIDTH / 2 ; x < WIN_WIDTH / 2 ; x++) {
		for (int y = -WIN_HEIGHT / 2 ; y < WIN_HEIGHT / 2; y++) {
			t_vec3f D = canvas_to_viewport(x, y);
			int color = rays_trace(O, D, 1, INF);
			put_pixel_canvas(frame, x, y, color);
		}
	}
}