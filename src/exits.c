/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exits.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 18:14:43 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/23 13:29:39 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdarg.h>

int	is_command(int serverpid, char *str)
{
	if (ft_strncmp(str, ":EXIT", 5) == 0)
	{
		ft_printf("%sEXIT Program...\n%s", GREEN, NORMAL);
		if (serverpid > 0)
			tx_char(serverpid, ENQ);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	signint_client_handler(int signum)
{
	static int	count = 0;

	(void)signum;
	if (count++ > 3)
	{
		ft_printf("\n\nCtrl-C pressed multiple times! Force exit...\n");
		exit(EXIT_FAILURE);
	}
	ft_printf("\n\nCtrl-C pressed, use :EXIT command for normal exit!\n");
	return ;
}

void	signint_server_handler(int signum)
{
	(void)signum;
	ft_printf("\n\nCtrl-C pressed, closing server...\n");
	exit(EXIT_SUCCESS);
}

void	exit_error(char *error, ...)
{
	char	*p;
	va_list	list;

	va_start(list, error);
	p = va_arg(list, char *);
	while (p > (char *)0x1000)
	{
		free(p);
		p = va_arg(list, char *);
	}
	ft_printf("%s%s\n%s", RED, error, NORMAL);
	exit(EXIT_FAILURE);
}
