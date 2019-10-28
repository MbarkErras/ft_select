/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:52:56 by merras            #+#    #+#             */
/*   Updated: 2019/10/28 20:21:26 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	termcaps_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	render_option(char *option, int mode)
{
	int i;

	if (F_GET(mode, F_SELECTED))
		tputs(tgetstr("mr", NULL), 1, termcaps_putchar);
	if (F_GET(mode, F_HOVERED))
		tputs(tgetstr("us", NULL), 1, termcaps_putchar);
	ft_putstr(option);
	i = ft_strlen(option) - 1;
	while (++i < CONFIG(field_size))	
		ft_putchar(' ');
	tputs(tgetstr("me", NULL), 1, termcaps_putchar);
	tputs(tgetstr("ue", NULL), 1, termcaps_putchar);
}

void	render_selection()
{
	int	i;

	tputs(tgetstr("cl", NULL), 1, termcaps_putchar);
	CONFIG(options_width) = CONFIG(wsize).ws_col / CONFIG(field_size);
	CONFIG(options_height) = CONFIG(options_count) / CONFIG(options_width) +
	!!(CONFIG(current_option) % CONFIG(options_width));
	i = 0;
	while (i < CONFIG(options_count))
	{
		render_option(CONFIG(options)[i], F_BGET(CONFIG(options_flags)[i], 3));
		if (i % CONFIG(options_width) == CONFIG(options_width) - 1)
			ft_putchar('\n');
		i++;
	}
}

void	move_option(char direction)
{
	if ((direction == U && CONFIG(current_option) < CONFIG(options_width)) ||
	(direction == D && CONFIG(current_option) / CONFIG(options_width) + 1 ==
	CONFIG(options_height)))
		return ;
	tputs(tgoto(tgetstr("cm", NULL), (CONFIG(current_option) %
	CONFIG(options_width)) * CONFIG(field_size), CONFIG(current_option) /
	CONFIG(options_width)), 1, termcaps_putchar);
	render_option(CONFIG(options)[CONFIG(current_option)],
	F_GET(CONFIG(options_flags)[CONFIG(current_option)], F_SELECTED));
	F_UNSET(CONFIG(options_flags)[CONFIG(current_option)], F_HOVERED);
	if (CONFIG(current_option) == 0 && direction == L)
		CONFIG(current_option) = CONFIG(options_count) - 1;
	else if (CONFIG(current_option) == CONFIG(options_count) - 1 &&
	direction == R)
		CONFIG(current_option) = 0;
	else if (direction == U || direction == D)
		CONFIG(current_option) += (direction == U ? -1 : 1) *
		CONFIG(options_width);
	else
		CONFIG(current_option) += direction == L ? -1 : 1;
	tputs(tgoto(tgetstr("cm", NULL), (CONFIG(current_option) %
	CONFIG(options_width)) * CONFIG(field_size), CONFIG(current_option) /
	CONFIG(options_width)), 1, termcaps_putchar);
	F_SET(CONFIG(options_flags)[CONFIG(current_option)], F_HOVERED);
	render_option(CONFIG(options)[CONFIG(current_option)],
	F_BGET(CONFIG(options_flags)[CONFIG(current_option)], 3));
}

void	select_option()
{
	if (F_GET(CONFIG(options_flags)[CONFIG(current_option)], F_SELECTED))
		F_UNSET(CONFIG(options_flags)[CONFIG(current_option)], F_SELECTED);
	else
		F_SET(CONFIG(options_flags)[CONFIG(current_option)], F_SELECTED);
	move_option(R);
}

void	cancel_selection()
{
	reset_input_mode();
	exit(0);
}

void	submit_options()
{
	int f;
	int	i;

	f = 0;
	i = -1;
	while (CONFIG(options)[++i])
	{

		if (F_GET(CONFIG(options_flags)[i], F_SELECTED) &&
		!F_GET(CONFIG(options_flags)[i], F_DELETED))
		{
			if (f)
				ft_putchar(' ');
			ft_putstr(CONFIG(options)[i]);
			f = 1;
		}
	}
}

void	delete_option(void)
{
	if (CONFIG(options_count) == 1)
		exit(0);
	F_SET(CONFIG(options_flags)[CONFIG(current_option)], F_DELETED);
	render_selection();
}













