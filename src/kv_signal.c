/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:21:45 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/13 18:18:25 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_child_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("signal SIGINT received\n");
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_sigstat = 130;
	}
}

void	kv_sigint_handler(int signo)
{
	(void)signo;
	if (g_sigstat == 2)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_sigstat = -1;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (g_sigstat == 1)
		ft_putstr_fd("\n", 1);
	else
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sigstat = 130;
}

void	kv_set_signals(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	sigint_act.sa_handler = kv_sigint_handler;
	sigint_act.sa_flags = SA_RESTART;
	sigemptyset(&sigint_act.sa_mask);
	sigaction(SIGINT, &sigint_act, NULL);
	sigquit_act.sa_handler = SIG_IGN;
	sigquit_act.sa_flags = 0;
	sigemptyset(&sigquit_act.sa_mask);
	sigaction(SIGQUIT, &sigquit_act, NULL);
}
