/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:18:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 11:19:23 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	push_col(t_scene *scene, t_collideable *col)
{
	ft_lstadd_back(&scene->collideables, ft_lstnew(col));
}

static void	parse_cylinder(t_engine *engine, char **params)
{
	t_vec2	dandh;

	dandh.x = parse_double(params[2]);
	dandh.y = parse_double(params[3]);
	push_col(&engine->scene, new_cylinder_col(parse_vec3(params[0]), \
			vec3_normalize(parse_vec3(params[1])), dandh, \
				parse_color(params[4])));
}

void	parse_object(t_engine *engine, char *type, char **params, t_counts *c)
{
	if (ft_strcmp(type, "A") == 0)
		parse_ambient(&engine->scene, params, c);
	else if (ft_strcmp(type, "C") == 0)
		parse_camera(&engine->scene, params, c);
	else if (ft_strcmp(type, "L") == 0)
		parse_light(&engine->scene, params);
	else if (ft_strcmp(type, "sp") == 0)
		push_col(&engine->scene, new_sphere_col(parse_vec3(params[0]), \
			parse_double(params[1]), parse_color(params[2])));
	else if (ft_strcmp(type, "pl") == 0)
		push_col(&engine->scene, new_plane_col(parse_vec3(params[0]), \
			vec3_normalize(parse_vec3(params[1])), parse_color(params[2])));
	else if (ft_strcmp(type, "cy") == 0)
		parse_cylinder(engine, params);
	else
		exit(plog(ERROR, "While parsing object type") || 1);
}
