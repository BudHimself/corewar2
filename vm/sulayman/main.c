/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:19:50 by syusof            #+#    #+#             */
/*   Updated: 2017/05/09 11:36:43 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int main()
{
	unsigned char	*tab;
	unsigned int	i;
	unsigned int	curs;
	int				carry;
	unsigned int	cycle_to_die1;

	tab = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE);
	i = 0;
	while (i < MEM_SIZE)
	{
		tab[i] = 0;
		i++;
	}
	tab[0] = 16;
	tab[1] = 52;
	tab[2] = 208;
	tab[3] = 111;
	tab[2048] = 1;
	tab[2049] = 255;
	tab[2050] = 255;
	tab[2051] = 255;
	tab[2052] = 254;

	/*
	tab[0] = 1;
	tab[1] = 255;
	tab[2] = 255;
	tab[3] = 255;
	tab[4] = 254;
*/

//	carry = 1;
//	ft_st(tab, 0, &(tab[0]), &(tab[100]));
//	ft_st(tab, 0, &(tab[0]), &(tab[200]));
//	ft_sti(tab, &(tab[0]), 20, -1);
//	ft_ld(tab,0,&carry, 0, &(tab[300]), -1);
//	ft_add(&carry, &(tab[0]), &(tab[2]), &(tab[200]));
//	ft_zjmp(tab, 0, &(tab[500]), 0,1);
	
	/*
	cycle_to_die1 = CYCLE_TO_DIE;
	while (cycle_to_die1 > 0)
	{

		cycle_to_die1 = cycle_to_die1 - CYCLE_DELTA;
	}
*/
/*
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % 32 == 0)
			printf("\n");
		printf("%02x ",tab[i]);
		i++;
	}
*/
	t_lst *lst1;

	lst1 = create_lst();
//	((t_process*)(lst1->content))->nblive = 12;
	LST1->num_player = -1;
	unsigned char	*a;
	a = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 0;
	LST1->pc = a;
	LST1->remain_cycle = -1;

	t_lst *lst2;

	lst2 = create_lst();
//	((t_process*)(lst2->content))->nblive = 22;
	((t_process*)(lst2->content))->num_player = -2;
	unsigned char	*b;
	b = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	b[0] = 0;
	b[1] = 0;
	b[2] = 8;
	b[3] = 0;
	((t_process*)(lst2->content))->pc = b;
	((t_process*)(lst2->content))->remain_cycle = -1;

//	lst1 = add_lst(&lst1,&lst2);
	lst1 = add_lst_down(&lst1,&lst2);

//	t_lst *lst3;

//	lst3 = create_lst();
//	((t_process*)(lst3->content))->nblive = 32;
//	lst1 = add_lst(&lst1,&lst3);
//	lst1 = add_lst_down(&lst1,&lst3);
//	lst1 = add_lst_between(&lst1,NULL,&lst3);
	
//	lst1 = del_lst_pos(&lst1, -1);
/*
	while (lst1)
	{
	printf("nbl = %d\n", ((t_process*)(lst1->content))->nblive);
	lst1 = lst1->next;
	}
*/
	printf("winner: %d\n",ft_launch(tab,lst1));





}
