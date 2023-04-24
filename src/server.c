/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 17:32:22 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 13:25:56 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	pidfix(int pid)
{
	static int	previous_pid = 0;

	if (pid != previous_pid && pid != 0)
		previous_pid = pid;
	else if (DEBUG && pid == 0)
		ft_printf("%sDEBUG: wrong PID: %d%s\n", RED, previous_pid, NORMAL);
	return (previous_pid);
}

static int	get_rx_len(char c)
{
	static int	rx_len = 0;

	if (c == SOH)
		rx_len = 0;
	else if (c >= '0' && c <= '9')
	{
		rx_len *= 10;
		rx_len += c - '0';
	}
	return (rx_len);
}

static int	set_status(char c)
{
	debug(c);
	if (c > 7)
		timeout_monitor(RESET);
	else if (c == SOH)
		timeout_monitor(START);
	else if (c == ETX)
		timeout_monitor(RESET);
	else if (c == EOT)
		timeout_monitor(STOP);
	else if (c == ENQ)
	{
		timeout_monitor(STOP);
		ft_printf("\n%sClient disconnected...\n%s", GREEN, NORMAL);
		info_message(getpid(), SERVER);
		return (true);
	}
	return (false);
}

static void	server_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit = (sizeof(c) << 3);
	static int				header = false;
	static int				rx_len = 0;

	(void)context;
	c |= (signum - SIGUSR1) << (bit - 1);
	bit -= 1;
	if (bit == 0)
	{
		bit = (sizeof(c) << 3);
		set_status(c);
		if (!header && c > BEL)
			if (buffer_and_print(c, rx_len))
				kill(pidfix(info->si_pid), SIGUSR2);
		if (c == STX)
			header = false;
		else if (c == SOH)
			header = true;
		if (header)
			rx_len = get_rx_len(c);
		c = 0;
	}
	kill(pidfix(info->si_pid), SIGUSR1);
	return ;
}

void	server(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
