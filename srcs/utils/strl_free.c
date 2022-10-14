/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strl_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:46:44 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/12 10:42:22 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Free the pointed list and set it to NULL.
 *
 * @param list Pointer to the list to free.
 */
void	strl_free(char ***list)
{
	int	i;

	if (!list || !*list)
		return ;
	i = 0;
	while ((*list)[i])
	{
		free((*list)[i]);
		i++;
	}
	free(*list);
	*list = NULL;
}
