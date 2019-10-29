/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_listener.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:26:04 by merras            #+#    #+#             */
/*   Updated: 2019/10/29 04:30:09 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	select_option(void)
{
	if (F_GET(TLIST(list_indexed_node(CONFIG(options), CONFIG(current_option)),
	t_option)->flags, F_SELECTED))
		F_UNSET(TLIST(list_indexed_node(CONFIG(options),
		CONFIG(current_option)), t_option)->flags, F_SELECTED);
	else
		F_SET(TLIST(list_indexed_node(CONFIG(options),
		CONFIG(current_option)), t_option)->flags, F_SELECTED);
	move_option(R);
}

void	submit_options(void)
{
	t_list	*option;
	int		f;

	f = 0;
	tputs(tgetstr("te", NULL), 1, termcaps_putchar);
	tputs(tgetstr("ve", NULL), 1, termcaps_putchar);
	CONFIG(current_option) = -1994;
	option = CONFIG(options);
	while (option)
	{
		if (F_GET(TLIST(option, t_option)->flags, F_SELECTED))
		{
			if (f)
				ft_putchar(' ');
			ft_putstr(TLIST(option, t_option)->value);
			f = 1;
		}
		option = option->next;
	}
}

void	delete_option(void)
{
	if (CONFIG(options_count) == 1)
		ft_select_exit();
	list_delete_node(&CONFIG(options), list_indexed_node(CONFIG(options),
				CONFIG(current_option)), t_option_delete);
	CONFIG(options_count) -= 1;
	if (CONFIG(current_option) == CONFIG(options_count))
		CONFIG(current_option) = CONFIG(options_count) - 1;
	F_SET(TLIST(list_indexed_node(CONFIG(options), CONFIG(current_option)),
				t_option)->flags, F_HOVERED);
	render_selection();
}

void	ft_select_listener_init(void)
{
	if (!is_enough_area())
		terminal_resized();
	else
		CONFIG(enough_terminal) = 1;
	render_selection();
}

void	ft_select_listener(void)
{
	char	buffer[4];

	ft_select_listener_init();
	ft_bzero(buffer, 4);
	while (read(0, buffer, 4))
	{
		if (CONFIG(enough_terminal))
		{
			if (IS_ARROW(buffer))
				move_option(buffer[2]);
			else if (buffer[0] == ' ' && !buffer[1])
				select_option();
			else if (IS_DELETE(buffer) || (buffer[0] == 127 && !buffer[1]))
				delete_option();
			else if (buffer[0] == ESC && !buffer[1])
				ft_select_exit();
			else if (buffer[0] == '\n' && !buffer[1])
			{
				submit_options();
				return ;
			}
			ft_bzero(buffer, 4);
		}
	}
}
