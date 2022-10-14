/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:56:49 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/12 10:41:45 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_words(char *str, char *delim)
{
	int	in_delim;
	int	visited;
	int	count;
	int	i;

	i = 0;
	count = 0;
	visited = 0;
	while (str[i])
	{
		in_delim = !!ft_strchr(delim, str[i]);
		if (!in_delim && !visited)
			count++;
		visited = !in_delim;
		i++;
	}
	return (count);
}

static char	*extract_word(char *str, char *delim)
{
	int	len;

	len = 0;
	while (!ft_strchr(delim, str[len]))
		len++;
	return (ft_substr(str, 0, len));
}

/**
 * @brief Splits a string into an array of words.
 *
 * @param str The string to split.
 * @param delim The delimiters to split the string with.
 * @return An array of words.
 */
char	**str_split(char *str, char *delim)
{
	char	**result;
	int		in_delim;
	int		visited;
	int		i;
	int		j;

	if (!str || !delim)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(str, delim) + 1));
	visited = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		in_delim = !!ft_strchr(delim, str[i]);
		if (!in_delim && !visited)
			result[j++] = extract_word(&str[i], delim);
		visited = !in_delim;
		i++;
	}
	result[j] = 0;
	return (result);
}
