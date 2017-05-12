/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:23:28 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/05 17:06:26 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	long	i;
	size_t	star_i;
	size_t	end_i;
	int		started;
	char	*result;

	i = -1;
	star_i = 0;
	end_i = 0;
	started = 0;
	while ((unsigned char)s[++i] != '\0')
	{
		if (ft_iswhitespace((char)s[i]) == 1)
			star_i = started ? star_i : i + 1;
		else
		{
			started = 1;
			end_i = i;
		}
	}
	end_i = started ? end_i : star_i;
	if (!(result = ft_strnew(end_i - star_i + 1)))
		return (NULL);
	return (ft_strncpy(result, s + star_i, end_i - star_i + 1));
}
