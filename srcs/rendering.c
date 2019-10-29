/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:52:56 by merras            #+#    #+#             */
/*   Updated: 2019/10/29 04:30:02 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		termcaps_putchar(int c)
{
	write(2, &c, 1);
	return (0);
}

void	render_option(t_list *option)
{
	int i;

	if (F_GET(TLIST(option, t_option)->flags, F_SELECTED))
		tputs(tgetstr("mr", NULL), 1, termcaps_putchar);
	if (F_GET(TLIST(option, t_option)->flags, F_HOVERED))
		tputs(tgetstr("us", NULL), 1, termcaps_putchar);
	ft_putstr_fd(TLIST(option, t_option)->value, 2);
	i = ft_strlen(TLIST(option, t_option)->value) - 1;
	while (++i < CONFIG(field_size))
		ft_putchar_fd(' ', 2);
	tputs(tgetstr("me", NULL), 1, termcaps_putchar);
	tputs(tgetstr("ue", NULL), 1, termcaps_putchar);
}

void	render_selection(void)
{
	t_list	*option;
	int		i;

	tputs(tgetstr("cl", NULL), 1, termcaps_putchar);
	CONFIG(options_width) = CONFIG(wsize).ws_col / CONFIG(field_size);
	CONFIG(options_height) = CONFIG(options_count) / CONFIG(options_width) +
		!!(CONFIG(current_option) % CONFIG(options_width));
	i = 0;
	option = CONFIG(options);
	while (option)
	{
		render_option(option);
		if (i % CONFIG(options_width) == CONFIG(options_width) - 1)
			ft_putchar_fd('\n', 2);
		option = option->next;
		i++;
	}
}

void	update_current_option(int direction)
{
	if (CONFIG(current_option) == 0 && direction == L)
		CONFIG(current_option) = CONFIG(options_count) - 1;
	else if (CONFIG(current_option) == (CONFIG(options_count) - 1) &&
			direction == R)
		CONFIG(current_option) = 0;
	else if (direction == U || direction == D)
		CONFIG(current_option) += (direction == U ? -1 : 1) *
			CONFIG(options_width);
	else
		CONFIG(current_option) += direction == L ? -1 : 1;
}

void	move_option(char direction)
{
	if ((direction == U && CONFIG(current_option) < CONFIG(options_width)) ||
	(direction == D && CONFIG(current_option) >= CONFIG(options_count) -
	CONFIG(options_width)))
		return ;
	tputs(tgoto(tgetstr("cm", NULL), (CONFIG(current_option) %
	CONFIG(options_width)) * CONFIG(field_size), CONFIG(current_option) /
	CONFIG(options_width)), 1, termcaps_putchar);
	F_UNSET(TLIST(list_indexed_node(CONFIG(options),
	CONFIG(current_option)), t_option)->flags, F_HOVERED);
	render_option(list_indexed_node(CONFIG(options), CONFIG(current_option)));
	update_current_option(direction);
	tputs(tgoto(tgetstr("cm", NULL), (CONFIG(current_option) %
	CONFIG(options_width)) * CONFIG(field_size), CONFIG(current_option) /
	CONFIG(options_width)), 1, termcaps_putchar);
	F_SET(TLIST(list_indexed_node(CONFIG(options),
	CONFIG(current_option)), t_option)->flags, F_HOVERED);
	render_option(list_indexed_node(CONFIG(options), CONFIG(current_option)));
}
