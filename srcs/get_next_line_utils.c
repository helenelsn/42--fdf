/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:05:22 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 03:29:24 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncat(char *line, char *buffer, int len)
{
	int		l_len;
	char	*tmp;
	int		i;

	if (!len)
		len = ft_strlen(buffer);
	i = -1;
	l_len = ft_strlen(line);
	tmp = malloc(sizeof(char) * (l_len + len + 1));
	if (!tmp)
		return (NULL);
	while (++i < l_len)
		tmp[i] = line[i];
	i = -1;
	while (++i < len)
		tmp[l_len + i] = buffer[i];
	tmp[l_len + i] = '\0';
	free(line);
	return (tmp);
}
