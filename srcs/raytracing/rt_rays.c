/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 11:07:08 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	double	r;
	t_vec3f	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	r = sphere.radius;
	CO = v3f_affect(O.x - sphere.center.x, O.y - sphere.center.y, O.z - sphere.center.z);
	a = v3f_dot_v3f(D, D);
	b = 2 * v3f_dot_v3f(CO, D);
	c = v3f_dot_v3f(CO, CO) -  r*r;
	discriminant = b*b - 4*a*c;
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
 * @param scene Current scene.
 * @return int 
 */
int	rays_trace(t_vec3f O, t_vec3f D, int t_min, int t_max, t_scene scene)
{
	int			i;
	t_vec2f		t;
	int			closest_t;
	t_sphere*	closest_sphere;

	closest_t = INF;
	closest_sphere = NULL;
	i = -1;
	while (++i < 3)
	{
		t = rays_intercept_sphere(O, D, scene.spheres[i]);
		if (t.x >= t_min && t.x <= t_max && t.x < closest_t)
		{
			closest_t = t.x;
			closest_sphere = &scene.spheres[i];
		}
		if (t.y >= t_min && t.y <= t_max && t.y < closest_t)
		{
			closest_t = t.y;
			closest_sphere = &scene.spheres[i];
		}
	}
	if (closest_sphere == NULL)
		return (create_trgb(0, 0, 0, 0));
	return (closest_sphere->color);
}

