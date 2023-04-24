/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 17:32:22 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 14:04:16 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	client_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		g_txcount--;
	if (signum == SIGUSR2)
		ft_printf("%sServer has received the message\n%s", GREEN, NORMAL);
}

static void	client_listen(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = client_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

static int	interactive_client(int serverpid)
{
	char	pid_str[10];
	char	str[100];
	int		i;

	info_message(serverpid, CLIENT);
	if (serverpid == 0)
	{
		ft_printf("Enter server PID: ");
		read(0, pid_str, 10);
		serverpid = ft_atoi(pid_str);
		is_command(serverpid, pid_str);
		if (serverpid <= 0)
			exit_error("Invalid PID", NULL);
	}
	while (true)
	{
		i = 0;
		while (i < 100)
			str[i++] = '\0';
		ft_printf("\nEnter string [max 100 chars]: ");
		read(0, str, 99);
		if (!is_command(serverpid, str))
			tx_package(serverpid, str);
	}
}

int	client(int argc, char **argv)
{
	char	*line;

	client_listen();
	if (argc == 3)
	{
		if (ft_atoi(argv[1]) <= 0)
			exit_error("Invalid PID", NULL);
		tx_package(ft_atoi(argv[1]), argv[2]);
		tx_char(ft_atoi(argv[1]), ENQ);
		exit (EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		info_message(ft_atoi(argv[1]), STDIN);
		line = get_next_line(STDIN_FILENO);
		while (line && !is_command(ft_atoi(argv[1]), line))
		{
			tx_package(ft_atoi(argv[1]), line);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
		tx_char(ft_atoi(argv[1]), ENQ);
		exit (EXIT_SUCCESS);
	}
	return (interactive_client(0));
}
