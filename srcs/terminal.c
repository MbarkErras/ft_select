/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 22:46:55 by merras            #+#    #+#             */
/*   Updated: 2019/10/29 03:58:43 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html
*/

static void	init_terminal_data(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (!termtype)
		exit(ft_perror(EXEC_NAME, NULL, N_TRM));
	success = tgetent(0, termtype);
	if (success < 0)
		exit(ft_perror(EXEC_NAME, NULL, A_TRM));
	if (!success)
		exit(ft_perror(EXEC_NAME, termtype, S_TRM));
}

static void	set_input_mode(void)
{
	struct termios	tattr;

	if (!isatty(STDIN_FILENO) || !isatty(2))
		exit(ft_perror(EXEC_NAME, NULL, N_TTY));
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void		reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &CONFIG(saved_attr));
}

void		init_terminal(void)
{
	init_terminal_data();
	tcgetattr(STDIN_FILENO, &CONFIG(saved_attr));
	set_input_mode();
}

void		terminal_resized(void)
{
	if (!is_enough_area())
	{
		tputs(tgetstr("cl", NULL), 1, termcaps_putchar);
		ft_perror(EXEC_NAME, NULL, T_SZE);
		CONFIG(enough_terminal) = 0;
	}
	else
	{
		ioctl(0, TIOCGWINSZ, &CONFIG(wsize));
		render_selection();
		CONFIG(enough_terminal) = 1;
	}
}
