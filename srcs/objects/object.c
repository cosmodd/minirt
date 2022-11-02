/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:05:16 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:22:03 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdio.h>

void	free_collideable(void *ptr)
{
	t_collideable	*collideable;

	collideable = (t_collideable *)ptr;
	free(collideable->ptr);
	free(collideable);
}

void	nearest_t(t_hit *hit, t_factors *f)
{
	double	t;

	t = -1;
	f->delta = f->b * f->b - 4 * f->a * f->c;
	f->sqrt_delta = sqrt(f->delta);
	if (f->delta < 0)
		return ((void)(hit->t = -1));
	f->t1 = (-f->b - f->sqrt_delta) / (2 * f->a);
	f->t2 = (-f->b + f->sqrt_delta) / (2 * f->a);
	if (isnan(f->t1) || (f->t1 < 0 && f->t2 < 0))
		return ((void)(hit->t = -1));
	if (f->t1 > 0 && f->t1 < f->t2)
		t = f->t1;
	else
		t = f->t2;
	hit->t = t;
}
