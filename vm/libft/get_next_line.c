/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:51:57 by tyassine          #+#    #+#             */
/*   Updated: 2016/06/20 17:22:36 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lst_txt	*ft_is_in_lst(int fd, t_lst_txt *lst)
{
	t_lst_txt	*new_txt;

	new_txt = lst;
	while (new_txt || new_txt != NULL)
	{
		if (fd == new_txt->fd)
			return (new_txt);
		new_txt = new_txt->next;
	}
	return ((t_lst_txt *)NULL);
}

t_lst_txt	*ft_lst_new_text(char *text, int fd, t_lst_txt *lst)
{
	t_lst_txt	*new_txt;

	if ((new_txt = (t_lst_txt *)malloc(sizeof(t_lst_txt))) == NULL)
		return (NULL);
	new_txt->fd = fd;
	new_txt->pos = 0;
	new_txt->text = text;
	new_txt->next = NULL;
	if (lst == NULL)
		lst = new_txt;
	else
		while (lst)
		{
			if (lst->next == NULL)
			{
				lst->next = new_txt;
				break ;
			}
			lst = lst->next;
		}
	return (new_txt);
}

char		*ft_get_line(t_lst_txt *text)
{
	char		*line;
	t_lst_txt	*next;
	size_t		len;
	size_t		loc;

	loc = text->pos;
	if (text->text)
	{
		len = ft_strclen((text->text) + loc, '\n');
		line = ft_strnew(len);
		ft_memcpy(line, ((text->text) + loc), len);
		text->pos = (loc + len + 1);
		if (text->pos >= ft_strlen(text->text))
		{
			free(text->text);
			text->text = NULL;
		}
		return ((char *)line);
	}
	next = text->next;
	text = next;
	return ((char *)NULL);
}

int			get_next_line(int const fd, char **line)
{
	static t_lst_txt	*lst_texts;
	t_lst_txt			*new_txt;
	char				buff[BUFF_SIZE + 1];
	char				*text;
	int					ret;

	if (BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!(new_txt = ft_is_in_lst(fd, lst_texts)))
	{
		text = ft_strnew(0);
		while ((ret = read(fd, buff, BUFF_SIZE)))
		{
			if (ret == -1)
				return (-1);
			buff[ret] = '\0';
			text = ft_strjoin(text, buff);
		}
		if (!(new_txt = ft_lst_new_text(text, fd, lst_texts)))
			return (-1);
		if (lst_texts == NULL)
			lst_texts = new_txt;
	}
	*line = ft_get_line(new_txt);
	return ((*line == NULL || line == NULL) ? 0 : 1);
}
