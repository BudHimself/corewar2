/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:13:07 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/25 13:35:32 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

t_op g_op_tab[17];

void			free_tab(t_tab *tab)
{
	size_t i;

	i = -1;
	while (++i < TAB_LEN)
		ft_memdel((void**)&TAB[i].name);
	ft_memdel((void**)&TAB);
}

/*
** print_if_op() print dans data->len le registre correspondant.
*/

void			print_if_op(t_tab *tab, size_t i, t_result *data)
{
	OPCODE = return_op_tab(TAB[i].name);
	data->tab = realloc(data->tab, data->len + 1);
	data->tab[data->len++] = OPCODE.num;
	if (OPCODE.byte_codage)
	{
		data->tab = realloc(data->tab, data->len + 1);
		data->tab[data->len++] = print_bytecode(tab, i, OPCODE.nb_arg);
	}
	data->addr = TAB[i].addr;
}

/*
** print_solution() repartie les data selon leur type
*/

void			print_solution(t_tab *tab, t_result *data)
{
	size_t	i;
	char	*buf;

	buf = NULL;
	i = -1;
	while (++i < TAB_LEN)
		if (TAB[i].type != LABEL)
		{
			if (TAB[i].type == OP)
				print_if_op(tab, i, data);
			else if (TAB[i].type == REG)
			{
				data->tab = realloc(data->tab, data->len + 1);
				data->tab[data->len++] = ft_atoi_u(TAB[i].name + 1);
			}
			else if (TAB[i].type == IND_PARAM)
				switch_and_print_shortint_to_bigendian(ft_atoi(TAB[i].name),
				data);
			else if (TAB[i].type == LABEL_PARAM || TAB[i].type == NUM_PARAM
			|| TAB[i].type == IND_LABEL)
				print_if_label_param_or_num_param(tab, i, data);
		}
	free_tab(tab);
}

/*
** create_file_and_print() initialise enregitre les datas dans le header,
** lance print_solution() ecrit le resultat dans le .cor, puis ecris le
** nombre doctet du fichier dans le header;
*/

void			create_file_and_print(t_tab tab, char *file_new_name,
t_header header, int option)
{
	int				fd_to_write;
	unsigned int	nb_byte;
	t_result		data;

	nb_byte = 0;
	data.len = 0;
	data.tab = ft_memalloc(sizeof(char));
	data.flag = option;
	if ((fd_to_write = open(file_new_name,
					O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) == -1)
		ft_error(__LINE__, __FILE__);
	header.magic = switch_and_print_int_to_bigendian(COREWAR_EXEC_MAGIC, NULL);
	header.prog_size = switch_and_print_int_to_bigendian(nb_byte, NULL);
	write(fd_to_write, &header, sizeof(t_header));
	print_solution(&tab, &data);
	write(fd_to_write, data.tab, data.len);
	lseek(fd_to_write, sizeof(header.magic) +
			sizeof(header.prog_name) + 3, SEEK_SET);
	nb_byte = switch_and_print_int_to_bigendian(data.len, NULL);
	write(fd_to_write, &nb_byte, sizeof(int));
	ft_printf("Writing output program to %s\n", file_new_name);
	ft_memdel((void**)&data.tab);
	close(fd_to_write);
}
