/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 02:09:12 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/04/23 13:29:03 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	timeout_monitor(int action)
{
	static int	run = 0;

	if (action == START)
		run = 1;
	else if (action == STOP)
		run = 0;
	else if (action == RESET)
		run = 1;
	if (run > 0)
	{
		run++;
		if (run > INT_MAX)
			exit_error("Client lost during transmiting.\n", NULL);
	}
}
