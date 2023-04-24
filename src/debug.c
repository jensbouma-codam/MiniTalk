/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 17:25:52 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 01:36:27 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	debug(char c)
{
	if (DEBUG && c <= 7 && c >= 0)
	{
		ft_printf("%sDEBUG: %d%s ", YELLOW, c, NORMAL);
		if (c == SOH)
			ft_printf("%sSOH%s", GREEN, NORMAL);
		else if (c == STX)
			ft_printf("%sSTX%s", GREEN, NORMAL);
		else if (c == ETX)
			ft_printf("%sETX%s", GREEN, NORMAL);
		else if (c == EOT)
			ft_printf("%sEOT%s", GREEN, NORMAL);
		else if (c == ENQ)
			ft_printf("%sENQ%s", GREEN, NORMAL);
		else if (c == ACK)
			ft_printf("%sACK%s", GREEN, NORMAL);
		else if (c == BEL)
			ft_printf("%sBEL%s", GREEN, NORMAL);
		ft_printf("\n");
	}
}
