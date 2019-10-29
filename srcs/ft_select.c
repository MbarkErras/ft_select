/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 01:51:05 by merras            #+#    #+#             */
/*   Updated: 2019/10/29 04:30:07 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*ft_select_config(t_select *set)
{
	static t_select	*get = NULL;

	if (set)
		get = set;
	return (get);
}

static void	generic_signal_handler(int s)
{
	if (s == SIGCONT)
	{
		init_terminal();
		tputs(tgetstr("ti", NULL), 1, termcaps_putchar);
		tputs(tgetstr("vi", NULL), 1, termcaps_putchar);
		render_selection();
		signal(SIGTSTP, generic_signal_handler);
	}
	else if (s == SIGTTOU || s == SIGTTIN || s == SIGTSTP)
	{
		reset_input_mode();
		tputs(tgetstr("te", NULL), 1, termcaps_putchar);
		tputs(tgetstr("ve", NULL), 1, termcaps_putchar);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\32");
	}
	else if (s == SIGWINCH)
		terminal_resized();
	else
		ft_select_exit();
}

static void	set_signal_handlers(void)
{
	int sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == 29 || sig == 23 || sig == 20 || sig == SIGURG)
			continue ;
		signal(sig, generic_signal_handler);
	}
}

static void	init_selection(int argc, char **argv)
{
	int i;

	set_signal_handlers();
	CONFIG(options_count) = argc;
	CONFIG(current_option) = 0;
	CONFIG(field_size) = 0;
	CONFIG(options) = NULL;
	while (--argc >= 0)
	{
		i = ft_strlen(argv[argc]);
		CONFIG(field_size) = CONFIG(field_size) < i ? i : CONFIG(field_size);
		list_push_back(&CONFIG(options), list_create_node(t_option_create(
		(t_option){ft_strdup(argv[argc]), 0}), sizeof(char *)));
	}
	CONFIG(field_size) += 1;
	F_SET(TLIST(CONFIG(options), t_option)->flags, F_HOVERED);
	ioctl(0, TIOCGWINSZ, &CONFIG(wsize));
}

int			main(int argc, char **argv)
{
	t_select	config;

	if (argc == 1)
		return (0);
	ft_select_config(&config);
	init_terminal();
	tputs(tgetstr("ti", NULL), 1, termcaps_putchar);
	tputs(tgetstr("vi", NULL), 1, termcaps_putchar);
	init_selection(argc - 1, argv + 1);
	ft_select_listener();
	ft_select_exit();
}
