/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 01:36:35 by merras            #+#    #+#             */
/*   Updated: 2019/10/24 14:09:39 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>

# include <term.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include "centropy.h"

# define EXEC_NAME "ft_select"
# define CONFIG(x) ft_select_config(NULL)->x

typedef struct	s_select
{
	char			**options;
	char			*options_flags;
	int				options_count;
	int				current_option;
	int				field_size;
	int				options_width;
	int				options_height;
	struct winsize	wsize;
	struct termios	saved_attr;
}				t_select;

t_select		*ft_select_config(t_select *set);

void			init_terminal(void);
void			reset_input_mode(void);
void			terminal_resized(void);
int				termcaps_putchar(int c);

int				is_enough_area(void);

void			ft_select_listener(void);
void			render_selection(void);
void			render_option(char *option, int mode);
void			move_option(char direction);
void			select_option(void);
void			delete_option(void);
void			cancel_selection(void);
void			submit_options(void);

# define F_SELECTED 0
# define F_HOVERED 1
# define F_DELETED 2

# define ESC 27
# define IS_CSI(x) ((x)[0] == ESC && (x)[1] == '[')
# define IS_UP(x) (IS_CSI(x) && (x)[2] == 'A')
# define IS_DOWN(x) (IS_CSI(x) && (x)[2] == 'B')
# define IS_RIGHT(x) (IS_CSI(x) && (x)[2] == 'C')
# define IS_LEFT(x) (IS_CSI(x) && (x)[2] == 'D')
# define IS_ARROW(x) (IS_UP(x) || IS_DOWN(x) || IS_RIGHT(x) || IS_LEFT(x))
# define IS_DELETE(x) (x[0] == 0 && x[1] == 0 && x[2] == 0 && x[3] == 0)

# define U 'A'
# define D 'B'
# define R 'C'
# define L 'D'

int				ft_perror(char *command, char *arg, int err);

# define T_SZE 7
# define N_TRM 8
# define A_TRM 9
# define S_TRM 10
# define N_TTY 11

# define T_SZE_T ": not enough area"
# define N_TRM_T ": specify a terminal type by setting TERM variable"
# define A_TRM_T ": could not access the termcap data base"
# define S_TRM_T ": terminal type is not defined: "
# define N_TTY_T ": not a terminal"

# define CONTINUE_CBACK(x) x; continue ;

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

#endif
