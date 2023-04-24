/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:27:15 by jbouma        #+#    #+#                 */
/*   Updated: 2023/04/24 17:37:04 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	buffer_and_print(char c, int rx_len)
{
	static int		length = 0;
	static int		count = 0;
	static char		*s = NULL;

	if (length != rx_len)
	{
		s = ft_calloc(sizeof(char), rx_len + 1);
		if (s == NULL)
			exit_error("Malloc failed!");
	}
	length = rx_len;
	s[count++] = c;
	if (count == rx_len)
	{
		write(1, s, rx_len);
		free(s);
		count = 0;
		rx_len = 0;
		length = 0;
		return (true);
	}
	return (false);
}
