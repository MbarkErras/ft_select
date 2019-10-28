/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 01:51:05 by merras            #+#    #+#             */
/*   Updated: 2019/10/28 19:53:53 by merras           ###   ########.fr       */
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

static void generic_signal_handler(int signal)
{
	if (signal == SIGCONT)
		init_terminal();
	else if (signal == SIGTTOU || signal == SIGTTIN || signal == SIGTSTP)
		reset_input_mode();
	else if (signal == SIGWINCH) 
		terminal_resized();
	else
	{
		reset_input_mode();
		exit (0);
	}
}

static void	set_signal_handlers(void)
{
	signal(SIGCONT, generic_signal_handler);
	signal(SIGWINCH, generic_signal_handler);
	signal(SIGTSTP, generic_signal_handler);
	signal(SIGUSR1, generic_signal_handler);
	signal(SIGUSR2, generic_signal_handler);
	signal(SIGPROF, generic_signal_handler);
	signal(SIGVTALRM, generic_signal_handler);
	signal(SIGXFSZ, generic_signal_handler);
	signal(SIGXCPU, generic_signal_handler);
	signal(SIGTERM, generic_signal_handler);
	signal(SIGALRM, generic_signal_handler);
	signal(SIGPIPE, generic_signal_handler);
	signal(SIGINT, generic_signal_handler);
	signal(SIGHUP, generic_signal_handler);
}

static void	init_selection(int argc, char **argv)
{
	int i;

	set_signal_handlers();
	if (!(CONFIG(options_flags) = ft_memalloc(argc)))
		exit(0);
	CONFIG(options_count) = argc;
	CONFIG(current_option) = 0;
	CONFIG(field_size) = 0;
	CONFIG(options) = NULL;
	while (--argc > 0)
	{
		i = ft_strlen(argv[argc]);
		CONFIG(field_size) = CONFIG(field_size) < i ? i : CONFIG(field_size);
		list_push_back(&CONFIG(options), ft_strdup(argv[argc]))
	}
	CONFIG(field_size)++;
	F_SET(CONFIG(options_flags)[0], F_HOVERED);
	ioctl(1, TIOCGWINSZ, &CONFIG(wsize));
}

int			main(int argc, char **argv)
{
	t_select	config;

	if (argc == 1)
		return (0);
	ft_select_config(&config);
	init_terminal();
	init_selection(argc - 1, argv + 1);
	ft_select_listener();
}
