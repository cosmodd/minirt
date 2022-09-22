/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:10:55 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 14:10:47 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
 * @brief Compute unit vector.
 * 
 * @param a 
 * @return t_vec3f 
 */
t_vec3f	v3f_normalize(t_vec3f a)
{
	t_vec3f	ret;
	double module;

	module = v3f_module(a);
	ret.x = a.x / module;
	ret.y = a.y / module;
	ret.z = a.z / module;
	return (ret);
}

/**
 * @brief Addition between two vec3f.
 * 
 * @param a 
 * @param b 
 * @return t_vec3f 
 */
t_vec3f	v3f_plus_v3f(t_vec3f a, t_vec3f b)
{
	t_vec3f	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

/**
 * @brief Substraction between two vec3f.
 * 
 * @param a Vec3f substracted.
 * @param b Vec3f to substract.
 * @return t_vec3f 
 */
t_vec3f	v3f_minus_v3f(t_vec3f a, t_vec3f b)
{
	t_vec3f	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

/**
 * @brief Obtain module of a vec3f.
 * 
 * @param a Vec3f.
 * @return double 
 */
double	v3f_module(t_vec3f a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/**
 * @brief Dot product of two vec3f.
 * 
 * @param a First vec3f.
 * @param b Second vec3f.
 * @return double 
 */
double	v3f_dot_v3f(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Dot product of a vec3f by a real number.
 * 
 * @param a The vec3f.
 * @param b The real number.
 * @return t_vec3f 
 */
t_vec3f	v3f_scale(t_vec3f a, double b)
{
	t_vec3f	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

/**
 * @brief Substraction of a vec3f by a real number.
 * 
 * @param a The vec3f.
 * @param b The real number.
 * @return t_vec3f 
 */
t_vec3f	v3f_minus(t_vec3f a, double b)
{
	t_vec3f	ret;

	ret.x = a.x - b;
	ret.y = a.y - b;
	ret.z = a.z - b;
	return (ret);
}

/**
 * @brief Affectation of a vec3f.
 * 
 * @param x
 * @param y 
 * @param z 
 * @return t_vec3f 
 */
t_vec3f	v3f_affect(double x, double y, double z)
{
	t_vec3f	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

/**
 * @brief Affectation of a vec3.
 * 
 * @param x
 * @param y 
 * @param z 
 * @return t_vec3 
 */
t_vec3	v3_affect(int x, int y, int z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

/**
 * @brief Dot product of a vec3 by a real number.
 * 
 * @param a The vec3.
 * @param b The real number.
 * @return t_vec3f 
 */
t_vec3	v3_scale(t_vec3 a, double b)
{
	t_vec3	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}
