/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:18:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/04 14:55:48 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	push_col(t_scene *scene, t_collideable *col)
{
	ft_lstadd_back(&scene->collideables, ft_lstnew(col));
}

static void	parse_cylinder(t_engine *e, char **params)
{
	t_vec2	dandh;

	dandh.x = parse_double(&e->scene, params[2]);
	dandh.y = parse_double(&e->scene, params[3]);
	push_col(&e->scene, new_cylinder_col(parse_vec3(&e->scene, params[0]), \
			vec3_normalize(parse_vec3(&e->scene, params[1])), dandh, \
				parse_color(&e->scene, params[4])));
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
		push_col(&e->scene, new_sphere_col(parse_vec3(&e->scene, params[0]), \
			parse_double(&e->scene, params[1]), \
				parse_color(&e->scene, params[2])));
	else if (ft_strcmp(type, "pl") == 0)
		push_col(&e->scene, new_plane_col(parse_vec3(&e->scene, params[0]), \
			vec3_normalize(parse_vec3(&e->scene, params[1])), \
				parse_color(&e->scene, params[2])));
	else if (ft_strcmp(type, "cy") == 0)
		parse_cylinder(e, params);
	else
		quit_error(&e->scene, (plog(ERROR, \
			"Unknown object type") || 1));
}
