/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:34:51 by merras            #+#    #+#             */
/*   Updated: 2019/10/29 04:30:01 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_option	*t_option_create(t_option o)
{
	t_option	*option;

	option = (t_option *)malloc(sizeof(t_option));
	option->value = o.value;
	option->flags = o.flags;
	return (option);
}

void		t_option_delete(void *o)
{
	free(((t_option *)o)->value);
	free(o);
}

void		ft_select_exit(void)
{
	list_delete(&CONFIG(options), t_option_delete);
	if (CONFIG(current_option) != -1994)
	{
		tputs(tgetstr("te", NULL), 1, termcaps_putchar);
		tputs(tgetstr("ve", NULL), 1, termcaps_putchar);
	}
	reset_input_mode();
	exit(0);
}
