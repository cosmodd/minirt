/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:06:35 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:53:10 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_log
{
	INFO,
	WARN,
	ERROR,
	DEBUG
}	t_log;

int		plog(t_log type, char *msg);
void	usage(void);

#endif
