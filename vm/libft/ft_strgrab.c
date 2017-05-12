/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strgrab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:32:52 by tyassine          #+#    #+#             */
/*   Updated: 2016/11/07 18:32:58 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strgrab(const char *str, char delim)
{
	int	i;

	i = 0;
	if (*str == 0)
		return (NULL);
	while (str[i] && str[i] != delim)
		i++;
	if (i)
		return (ft_strndup(str, i));
	return (NULL);
}
