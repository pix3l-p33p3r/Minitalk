/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-yak <elel-yak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:41:07 by elel-yak          #+#    #+#             */
/*   Updated: 2023/02/12 13:30:42 by elel-yak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	ft_infos(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (sig == SIGUSR2)
		return ;
	ft_putstr("Sent successfuly!\n");
	exit(EXIT_FAILURE);
}

static void	ft_last_bit(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_putstr("\nError : Kill failed\n");
		usleep(10);
	}
}

static void	ft_error(void)
{
	ft_putstr("\nError : Invalid PID\n");
	exit(EXIT_FAILURE);
}

static void	send_to_server(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR1) == -1)
					ft_error();
			}
			else
				if (kill(pid, SIGUSR2) == -1)
					ft_error();
			usleep(50);
		}
	}
	ft_last_bit(pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr("Arguments :  ./client [pid] [string]\n");
		exit(0);
	}
	sa.sa_sigaction = ft_infos;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		exit(EXIT_FAILURE);
	send_to_server(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
