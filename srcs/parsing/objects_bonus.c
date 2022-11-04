/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:18:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/04 10:19:50 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	push_col(t_scene *scene, t_collideable *col)
{
	ft_lstadd_back(&scene->collideables, ft_lstnew(col));
}

static void	parse_cylinder(t_engine *e, char **params)
{
	t_vec3_vec3	pdc;
	t_vec2		dh;
	t_vec2		sr;

	pdc.x = parse_vec3(&e->scene, params[0]);
	pdc.y = vec3_normalize(parse_vec3(&e->scene, params[1]));
	dh.x = parse_double(&e->scene, params[2]);
	dh.y = parse_double(&e->scene, params[3]);
	sr.x = parse_double(&e->scene, params[4]);
	if (!sr.x)
		sr.x = -1;
	sr.y = parse_double(&e->scene, params[5]);
	if (sr.y > 1 || sr.y < 0)
		quit_error(&e->scene, ((plog(ERROR, \
			"Reflection expected range [0-1]") & 0) | 1));
	pdc.z = parse_color(&e->scene, params[6]);
	push_col(&e->scene, new_cylinder_col(pdc, dh, sr));
}

static void	parse_sphere(t_engine *e, char **params)
{
	t_vec3	dsr;
	t_vec3	pos;
	t_vec3	color;

	pos = parse_vec3(&e->scene, params[0]);
	dsr.x = parse_double(&e->scene, params[1]);
	dsr.y = parse_double(&e->scene, params[2]);
	if (!dsr.y)
		dsr.y = -1;
	dsr.z = parse_double(&e->scene, params[3]);
	if (dsr.z > 1 || dsr.z < 0)
		quit_error(&e->scene, ((plog(ERROR, \
			"Reflection expected range [0-1]") & 0) | 1));
	color = parse_color(&e->scene, params[4]);
	push_col(&e->scene, new_sphere_col(pos, dsr, color));
}

static void	parse_plane(t_engine *e, char **params)
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec2	sr;
	t_vec3	color;

	pos = parse_vec3(&e->scene, params[0]);
	dir = vec3_normalize(parse_vec3(&e->scene, params[1]));
	sr.x = parse_double(&e->scene, params[2]);
	if (!sr.x)
		sr.x = -1;
	sr.y = parse_double(&e->scene, params[3]);
	if (sr.y > 1 || sr.y < 0)
		quit_error(&e->scene, ((plog(ERROR, \
			"Reflection expected range [0-1]") & 0) | 1));
	color = parse_color(&e->scene, params[4]);
	push_col(&e->scene, new_plane_col(pos, dir, sr, color));
}

void	parse_object(t_engine *e, char *type, char **params, t_counts *c)
{
	if (ft_strcmp(type, "A") == 0)
		parse_ambient(&e->scene, params, c);
	else if (ft_strcmp(type, "C") == 0)
		parse_camera(&e->scene, params, c);
	else if (ft_strcmp(type, "L") == 0)
		parse_light(&e->scene, params);
	else if (ft_strcmp(type, "sp") == 0)
		parse_sphere(e, params);
	else if (ft_strcmp(type, "pl") == 0)
		parse_plane(e, params);
	else if (ft_strcmp(type, "cy") == 0)
		parse_cylinder(e, params);
	else
		quit_error(&e->scene, (plog(ERROR, \
			"Unknown object type") || 1));
}
