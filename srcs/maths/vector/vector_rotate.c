/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:33:21 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/29 16:19:00 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2_rotate(t_vec2 vec, double angle)
{
	t_vec2	rotated;
	double	ca;
	double	sa;

	ca = cos(angle);
	sa = sin(angle);
	rotated.x = vec.x * ca - vec.y * sa;
	rotated.y = vec.x * sa + vec.y * ca;
	return (rotated);
}

t_vec3	vec3_rotate(t_vec3 vec, t_vec3 axis, double angle)
{
	t_vec3	rotated;
	t_vec2	xaxis;
	t_vec2	yaxis;
	t_vec2	zaxis;

	xaxis = (t_vec2){cos(-angle * axis.x), sin(-angle * axis.x)};
	yaxis = (t_vec2){cos(-angle * axis.y), sin(-angle * axis.y)};
	zaxis = (t_vec2){cos(-angle * axis.z), sin(-angle * axis.z)};
	
	rotated.x = vec.x * (yaxis.x * zaxis.x) + vec.y * (xaxis.y * yaxis.y * zaxis.x - xaxis.x * zaxis.y) + vec.z * (xaxis.x * yaxis.y * zaxis.x + xaxis.y * zaxis.y);
	rotated.y = vec.x * (yaxis.x * zaxis.y) + vec.y * (xaxis.y * yaxis.y * zaxis.y + xaxis.x * zaxis.x) + vec.z * (xaxis.x * yaxis.y * zaxis.y - xaxis.y * zaxis.x);
	rotated.z = vec.x * (-yaxis.y) + vec.y * (xaxis.y * yaxis.x) + vec.z * (xaxis.x * yaxis.x);
	return (rotated);
}

/*
⌈ cos(β) cos(θ) | sin(α) sin(β) cos(θ) - cos(α) sin(θ) | cos(α) sin(β) cos(θ) + sin(α) sin(θ) ⌉
| cos(β) sin(θ) | sin(α) sin(β) sin(θ) + cos(α) cos(θ) | cos(α) sin(β) sin(θ) - sin(α) cos(θ) |
⌊ -sin(β)       | sin(α) cos(β)                        | cos(α) cos(β)                        ⌋

⌈ x cos(β) cos(θ) + y sin(α) sin(β) cos(θ) - y cos(α) sin(θ) + z cos(α) sin(β) cos(θ) + z sin(α) sin(θ) ⌉
| x cos(β) sin(θ) + y sin(α) sin(β) sin(θ) + y cos(α) cos(θ) + z cos(α) sin(β) sin(θ) - z sin(α) cos(θ) |
⌊ -x sin(β) + y sin(α) cos(β) + z cos(α) cos(β)                                                         ⌋



 */