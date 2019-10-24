/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:52:56 by merras            #+#    #+#             */
/*   Updated: 2019/10/24 08:26:20 by merras           ###   ########.fr       */
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
	char padding[CONFIG(field_size) - 1];

	ft_memset(padding, ' ', CONFIG(field_size) - 1);
	if (mode == F_SELECTED)
		tputs(tgetstr("mr", NULL), 1, termcaps_putchar);
	if (mode == F_HOVERED)
		tputs(tgetstr("us", NULL), 1, termcaps_putchar);
	ft_putstr(option);
	ft_putstr(padding + ft_strlen(option));
	tputs(tgetstr("me", NULL), 1, termcaps_putchar);
	tputs(tgetstr("ue", NULL), 1, termcaps_putchar);
}

void	render_selection()
{
	int	i;

	tputs(tgetstr("cl", NULL), 1, termcaps_putchar);
	CONFIG(options_width) = CONFIG(wsize).ws_cols / CONFIG(field_size);
	CONFIG(options_height) = CONFIG(wsize).ws_rows;
	i = 0;
	while (i < CONFIG(options_count))
	{
		render_option(CONFIG(options)p[i], F_BGET(CONFIG(options_flags, 8)));
		ft_putchar(' ');
		if (i % CONFIG(options_width) == CONFIG(option_width) - 1)
			ft_putchar('\n');
	}
}
