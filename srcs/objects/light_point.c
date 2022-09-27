/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:55:58 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/26 15:10:42 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*new_light_point(t_vec3 pos, double intensity, t_vec3 color)
{
	t_light	*light_point;

	light_point = malloc(sizeof(t_light));
	if (light_point == NULL)
		return (NULL);
	light_point->position = pos;
	light_point->intensity = intensity;
	light_point->color = color;
	return (light_point);
}
