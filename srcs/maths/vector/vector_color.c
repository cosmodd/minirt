/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:31:23 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:23:52 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3_from_rgba(int color)
{
	return ((t_vec3){
		.x = (color >> 16) & 0xff,
		.y = (color >> 8) & 0xff,
		.z = color & 0xff});
}

int	vec3_to_rgba(t_vec3 color)
{
	return (
		((int)color.x & 0xff) << 16
		| ((int)color.y & 0xff) << 8
		| ((int)color.z & 0xff));
}
