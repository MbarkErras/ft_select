/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:29:55 by merras            #+#    #+#             */
/*   Updated: 2019/10/24 08:20:03 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	is_enough_area(void)
{
	struct winsize	wsize;
	int				capacity;

	ioctl(1, TIOCGWINSZ, &wsize);
	capacity = wsize.ws_cols / CONFIG(field_size) * wsize.ws_rows;
	return (capacity >= CONFIG(options_count));
}
