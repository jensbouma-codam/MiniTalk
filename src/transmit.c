/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transmit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 17:07:29 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 13:53:28 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	continue_on_cts(void)
{
	static int	timeout = 0;

	while (g_txcount > 0)
	{
		timeout++;
		if (timeout > INT_MAX)
			exit_error("Server timeout, exiting program.\n", NULL);
	}
	timeout = 0;
}

void	tx_char(int serverpid, unsigned char c)
{
	int	i;

	i = (sizeof(c) << 3);
	debug(c);
	continue_on_cts();
	while (i)
	{	
		g_txcount++;
		if (kill (serverpid, SIGUSR1 + (c >> (i - 1) & 1)))
			exit_error("PID unreachable, exiting program.\n", NULL);
		i--;
		continue_on_cts();
	}
}

static void	tx_str(int serverpid, char *str)
{
	int	i;

	i = 0;
	if (DEBUG)
		ft_printf("%sSending string %s\n%s", GREEN, str, NORMAL);
	while (str[i])
		tx_char(serverpid, str[i++]);
}

int	tx_package(int serverpid, char *str)
{
	char	*strlen;

	strlen = ft_itoa(ft_strlen(str));
	if (DEBUG)
		ft_printf("%sSending data to server...\n%s", GREEN, NORMAL);
	tx_char(serverpid, SOH);
	tx_str(serverpid, strlen);
	free(strlen);
	tx_char(serverpid, STX);
	tx_str(serverpid, str);
	tx_char(serverpid, ETX);
	tx_char(serverpid, EOT);
	return (true);
}
