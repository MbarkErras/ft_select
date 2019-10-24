/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 01:36:35 by merras            #+#    #+#             */
/*   Updated: 2019/10/24 08:26:18 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_SELECT_H
# define FT_SELECT_H

#include <term.h>
#include <unistd.h>
#include "centropy.h"

# define EXEC_NAME "ft_select"
# define CONFIG(x) ft_select_config(NULL)->x

typedef strcut	s_select
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

void			init_terminal(void);

# define F_SELECTED 0
# define F_DELETED 1
# define F_HOVERED 2

# define IS_CSI(x) ((x)[0] == ESC && (x)[1] == '[')
# define IS_UP(x) (IS_CSI(x) && (x)[2] == 'A')
# define IS_DOWN(x) (IS_CSI(x) && (x)[2] == 'B')
# define IS_RIGHT(x) (IS_CSI(x) && (x)[2] == 'C')
# define IS_LEFT(x) (IS_CSI(x) && (x)[2] == 'D')
# define IS_ARROW(x) (IS_UP(x) || IS_DOWN(x) || IS_RIGH(x) || IS_LEFT(x))
# define IS_DELETE(x) (x[0] == 0 && x[1] == 0 && x[2] == 0 && x[3] == 0)


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

#endif