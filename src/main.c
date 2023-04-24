/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 13:21:05 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 13:46:02 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_txcount = 0;

int	main(int argc, char **argv)
{
	if (argc >= 1 && ft_strstr(argv[0], "client"))
	{
		signal(SIGINT, signint_client_handler);
		client(argc, argv);
	}
	signal(SIGINT, signint_server_handler);
	info_message(getpid(), SERVER);
	server();
	while (true)
		timeout_monitor(KEEP);
}

void	info_message(int serverpid, int modus)
{
	if (modus == SERVER)
	{
		ft_printf("%sServer PID: %d\n%s", GREEN, serverpid, NORMAL);
		ft_printf("Waiting for client to send data...\n");
	}
	else if (modus == CLIENT)
	{
		ft_printf("\n%sInvalid number of arguments given!\n", YELLOW);
		ft_printf("Run client as: ./bin/client [PID] 'message to send' OR ");
		ft_printf("cat file.txt | client [PID])\n\n");
		ft_printf("%sClient started in interactive mode\n\n%s", GREEN, NORMAL);
		ft_printf("%sCOMMANDS :EXIT to exit\n\n%s", GREEN, NORMAL);
		if (serverpid == 0)
			ft_printf("No server PID given as argument.\n");
		else
			ft_printf("Server PID: %d\n\n", serverpid);
	}
	else if (modus == STDIN)
	{
		ft_printf("%sClient reading from STDIN...\n%s", GREEN, NORMAL);
		ft_printf("%sIf STDIN isn't piped, type to send\n%s", GREEN, NORMAL);
		ft_printf("%sor use command :EXIT to exit program\n\n%s", GREEN, NORMAL);
	}
}
