/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 13:58:09 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 13:48:09 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define DEBUG 0

# define SOH 1
# define STX 2
# define ETX 3
# define EOT 4
# define ENQ 5
# define ACK 6
# define BEL 7

# define NORMAL  "\x1B[0m"
# define RED  "\x1B[31m"
# define GREEN  "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE  "\x1B[34m"
# define MAGNENTA  "\x1B[35m"
# define CYAAN  "\x1B[36m"
# define WHITE  "\x1B[37m"

# define SERVER 0
# define CLIENT 1
# define STDIN 2

# define KEEP 0
# define START 1
# define STOP 2
# define RESET 3

# include <stdbool.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# include "../lib/LibFT/include/libft.h"

// main.c
int		g_txcount;
int		main(int argc, char **argv);
void	info_message(int serverpid, int modus);

// client.c
int		client(int argc, char **argv);

// server.c
void	server(void);

// transmit.c
void	tx_char(int serverpid, unsigned char c);
int		tx_package(int serverpid, char *string);

// receive.c
int		buffer_and_print(char c, int rx_len);

// monitor.c
void	timeout_monitor(int action);

// debug.c
void	debug(char c);

//exits.c
int		is_command(int serverpid, char *str);
void	signint_client_handler(int signum);
void	signint_server_handler(int signum);
void	exit_error(char *error, ...);

#endif
