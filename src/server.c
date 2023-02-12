/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-yak <elel-yak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:41:07 by elel-yak          #+#    #+#             */
/*   Updated: 2023/02/12 19:18:53 by elel-yak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	handle_response(unsigned int *client_pid)
{
	kill(*client_pid, SIGUSR1);
	*client_pid = 0;
}

static void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{
	static unsigned char	received_byte = 0;
	static int				bit_count = 0;
	static unsigned int		client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	received_byte |= (signal == SIGUSR2);
	if (++bit_count == 8)
	{
		bit_count = 0;
		if (!received_byte)
			return (handle_response(&client_pid));
		ft_putchar(received_byte);
		received_byte = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		received_byte = received_byte << 1;
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Mandatory part!\n");
	ft_putstr("Server is running\n");
	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
