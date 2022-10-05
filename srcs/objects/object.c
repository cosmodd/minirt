/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:05:16 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/05 10:38:12 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	free_collideable(void *ptr)
{
	t_collideable	*collideable;

	collideable = (t_collideable *)ptr;
	free(collideable->ptr);
	free(collideable);
}