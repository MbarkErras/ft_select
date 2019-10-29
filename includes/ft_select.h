/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 01:36:35 by merras            #+#    #+#             */
/*   Updated: 2019/10/29 04:29:59 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>

# include <term.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include "centropy.h"
# include "simplist.h"

# define EXEC_NAME "ft_select"
# define CONFIG(x) ft_select_config(NULL)->x

typedef struct		s_option
{
	char			*value;
	char			flags;
}					t_option;

t_option			*t_option_create(t_option o);
void				t_option_delete(void *o);

typedef struct		s_select
{
	t_list			*options;
	t_list			*current_option_node;
	int				options_count;
	int				current_option;
	int				field_size;
	int				options_width;
	int				options_height;
	int				enough_terminal;
	struct winsize	wsize;
	struct termios	saved_attr;
}					t_select;

t_select			*ft_select_config(t_select *set);

void				ft_select_exit(void);

void				init_terminal(void);
void				reset_input_mode(void);
void				terminal_resized(void);
int					termcaps_putchar(int c);

int					is_enough_area(void);

void				ft_select_listener(void);
void				render_selection(void);
void				render_option(t_list *option);
void				move_option(char direction);
void				select_option(void);
void				delete_option(void);
void				cancel_selection(void);
void				submit_options(void);

# define F_SELECTED 0
# define F_HOVERED 1

# define ESC 27
# define IS_CSI(x) ((x)[0] == ESC && (x)[1] == '[')
# define IS_UP(x) (IS_CSI(x) && (x)[2] == 'A')
# define IS_DOWN(x) (IS_CSI(x) && (x)[2] == 'B')
# define IS_RIGHT(x) (IS_CSI(x) && (x)[2] == 'C')
# define IS_LEFT(x) (IS_CSI(x) && (x)[2] == 'D')
# define IS_ARROW(x) (IS_UP(x) || IS_DOWN(x) || IS_RIGHT(x) || IS_LEFT(x))
# define IS_DELETE(x) (x[0] == 27 && x[1] == '[' && x[2] == '3' && x[3] == '~')

# define U 'A'
# define D 'B'
# define R 'C'
# define L 'D'

int					ft_perror(char *command, char *arg, int err);

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

# define TLIST(name, type) ((type *)name->content)

#endif
