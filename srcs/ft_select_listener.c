/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_listener.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:26:04 by merras            #+#    #+#             */
/*   Updated: 2019/10/24 08:26:25 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_select_listener();
{
	char	buffer[4];

	render_selection();
	ft_bzero(buffer, 4);
	while(read(0, buffer, 4))
	{
		if (IS_ARROW(buffer))
			move_option();
		else if (buffer[0] == ' ' && !buffer[1])
			select_option();
		else if (IS_DELETE(buffer) || (buffer[0] == 127 && !buffer[1]))
			delete_option();
		else if (buffer[0] == ESC && !buffer[1])
			cancel_selection();
		else if (buffer[0] == '\n' && !buffer[1])
		{
			submit_options();
			return ;
		}
		ft_bzero(buffer, 4);
	}
}
