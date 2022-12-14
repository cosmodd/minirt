/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:51:29 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/20 14:15:30 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xutils.h"

int	rgba(int r, int g, int b, int a)
{
	return (
		(a & 0xff) << 24
		| (r & 0xff) << 16
		| (g & 0xff) << 8
		| (b & 0xff));
}
