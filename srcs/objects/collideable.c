/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collideable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:10:55 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 11:09:43 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_collideable	*to_collideable(t_object type, void *object)
{
	t_collideable	*collideable;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = type;
	collideable->object = object;
	return (collideable);
}
