/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:40:37 by merras            #+#    #+#             */
/*   Updated: 2019/10/24 08:26:21 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*ft_strerror(int err)
{
	if (err == T_SZE || err == N_TRM)
		return (err == T_SZE ? T_SZE_T : N_TRM_T);
	if (err == A_TRM || err == S_TRM)
		return (err == A_TRM ? A_TRM_T : S_TRM_T);
	if (err == N_TTY)
		return (N_TTY_T);
	return (NULL);
}

int		ft_perror(char *command, char *arg, int err)
{
	if (command)
		ft_putstr_fd(command, 2);
	ft_putstr_fd(ft_strerror(err), 2);
	if (arg)
		ft_putendl_fd(arg, 2);
	else
		ft_putchar_fd('\n', 2);
	return (err);
}
