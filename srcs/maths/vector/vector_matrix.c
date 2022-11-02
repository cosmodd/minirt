/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:14:42 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:26:08 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
 * @brief Multiply a vector by a matrix
 *
 * @param vec The vector to multiply
 * @param mat The matrix to multiply
 * @return t_vec3 The result of the multiplication
 */
t_vec3	vec3_mat4(t_vec3 vec, t_mat4 mat)
{
	return ((t_vec3){
		vec.x * mat.m[0][0] \
			+ vec.y * mat.m[0][1] \
				+ vec.z * mat.m[0][2] \
					+ mat.m[0][3],
		vec.x * mat.m[1][0] \
			+ vec.y * mat.m[1][1] \
				+ vec.z * mat.m[1][2] \
					+ mat.m[1][3],
		vec.x * mat.m[2][0] \
			+ vec.y * mat.m[2][1] \
				+ vec.z * mat.m[2][2] \
					+ mat.m[2][3]
	});
}
