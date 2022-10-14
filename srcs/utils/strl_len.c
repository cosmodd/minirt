/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strl_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:48:09 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/14 09:48:31 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	strl_len(char **str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}