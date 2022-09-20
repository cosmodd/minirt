/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:10:55 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/20 16:25:26 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathutils.h"

// TODO
// - Explain methods (also change methods name - more explicit)

t_vec3f	vec_dot_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	ret;

	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return (ret);
}

t_vec3f	vec_scale(t_vec3f a, double b)
{
	t_vec3f	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

t_vec3f	vec_minus(t_vec3f a, double b)
{
	t_vec3f	ret;

	ret.x = a.x - b;
	ret.y = a.y - b;
	ret.z = a.z - b;
	return (ret);
}