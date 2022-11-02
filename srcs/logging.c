/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:53:13 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:52:36 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

int	plog(t_log type, char *msg)
{
	char	*prefix;

	prefix = "\e[1;37;44m INFO \e[0m";
	if (type == WARN)
		prefix = "\e[1;37;43m WARN \e[0m";
	else if (type == ERROR)
		prefix = "\e[1;37;41m ERROR \e[0m";
	else if (type == DEBUG)
		prefix = "\e[1;37;45m DEBUG \e[0m";
	return (printf("%s\e[1;37m %s \e[0m\n", prefix, msg));
}

void	usage(void)
{
	printf("\n \e[1;3;37;44m USAGE \e[0m\n\n");
	printf(" \e[37;3m./minirt \e[0m");
	printf("\e[33;1;3m<scene.rt> \e[0m");
	printf("\n\n");
	printf(" \e[90;3m<arg> -> required argument.\e[0m\n");
	printf(" \e[90;3m[arg] -> optional argument.\e[0m\n");
	printf("\n");
}
