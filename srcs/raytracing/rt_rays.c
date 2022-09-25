/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/25 02:51:55 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Find if a ray intercept a sphere.
 * Quadratic equation obtained from : the equation for
 * all points on a sphere && the equation from all points on
 * a ray.
 *
 * @param O Origin of the ray (camera).
 * @param D Direction of the ray (viewport square).
 * @param sphere
 * @return t_vec2f
 */
t_vec2	rays_intercept_sphere(t_vec3 O, t_vec3 D, t_sphere sphere)
{
	t_vec2	t;
	double	r;
	t_vec3	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	r = sphere.radius;
	CO = vec3_sub(O, sphere.center);
	a = vec3_dot(D, D);
	b = 2.0 * vec3_dot(CO, D);
	c = vec3_dot(CO, CO) - r * r;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		t = (t_vec2){INF, INF};
	else
	{
		t.x = (-b + sqrt(discriminant)) / (2.0 * a);
		t.y = (-b - sqrt(discriminant)) / (2.0 * a);
	}
	return (t);
}

/**
 * @brief Compute the intensity I of the different light sources
 * in the scene, for a specific point.
 *
 * @param P Point to compute light intensity.
 * @param N Normal of the point in relation to its surface.
 * @param scene Current scene.
 * @return double - intensity I.
 */
double	compute_lighting(t_vec3	P, t_vec3 N, t_scene scene)
{
	double	i;
	t_vec3	L;
	double	N_dot_L;

	i = 0;
	i += scene.l_a.intensity;
	for (int k = 0 ; k < 2; k++)
	{
		L = vec3_sub(scene.l_p[k].pos, P);
		N_dot_L = vec3_dot(N, L);
		if (N_dot_L > 0)
			i += scene.l_p[k].intensity * (N_dot_L / (vec3_magnitude(N) * vec3_magnitude(L)));
	}
	if (i > 1)
		i = 1;
	return (i);
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
int	rays_trace(t_vec3 O, t_vec3 D, int t_min, int t_max, t_scene scene)
{
	int			i;
	t_vec2		t;
	double			closest_t;
	t_sphere*	closest_sphere;
	t_vec3		P;
	t_vec3		N;
	t_vec3		v_color;

	closest_t = INF;
	closest_sphere = NULL;
	i = -1;
	while (++i < 4)
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
	// Lighting compute
	P = vec3_add(O, vec3_scalar(D, closest_t)); // Compute intersection point
	N = vec3_sub(P, closest_sphere->center); // Compute intersection normal
	N = vec3_normalize(N);
	v_color = vec3_scalar(closest_sphere->color, compute_lighting(P, N, scene));
	return (create_trgb(0, v_color.x, v_color.y, v_color.z));
}

