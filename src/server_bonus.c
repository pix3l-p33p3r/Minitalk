/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-yak <elel-yak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:41:07 by elel-yak          #+#    #+#             */
/*   Updated: 2023/02/18 16:04:38 by elel-yak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	response(unsigned int *pid)
{
	if (kill(*pid, SIGUSR2) == -1)
		ft_putstr("\nError : Kill() failed\n");
	*pid = 0;
}

static void	handler_s(int sig, siginfo_t *siginfo, void *cntxt)
{
	static unsigned char	c = 0;
	static int				i = 0;
	static unsigned int		pid = 0;

	(void)cntxt;
	if (!pid)
		pid = siginfo->si_pid;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
			return (response(&pid));
		ft_putchar(c);
		c = 0;
		kill(pid, SIGUSR1);
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server is running !\n");
	ft_putstr(" PID : ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	sa.sa_sigaction = handler_s;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		ft_putstr("\nError : Kill has failed\n");
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		ft_putstr("\nError : Kill has failed\n");
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
