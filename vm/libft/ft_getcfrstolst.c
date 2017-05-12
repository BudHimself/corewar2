/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcfrstolst.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:35:15 by tyassine          #+#    #+#             */
/*   Updated: 2016/11/07 18:35:26 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_getcfrstolst(char *str, char delim, int last)
{
	int	i;

	i = 0;
	if (last)
	{
		while (str[i])
			i++;
		while (i >= 0 && str[--i])
		{
			if (str[i] == delim)
				return (i);
		}
	}
	else
		while (str[i])
		{
			if (str[i] == delim)
				return (i);
			i++;
		}
	if (!str[i])
		return (-1);
	return (0);
}
