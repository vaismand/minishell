/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:21:45 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 15:12:21 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//file for initializing and handling the signals

// handles the signal
void	kv_sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// sets the signals for SIGINT and SIGQUIT(CTRL-\ ignored)
void	kv_set_signals(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	sigint_act.sa_handler = kv_sigint_handler;
	sigint_act.sa_flags = SA_RESTART;
	sigemptyset(&sigint_act.sa_mask);
	sigaddset(&sigint_act.sa_mask, SIGINT);
	sigaction(SIGINT, &sigint_act, NULL);
	sigquit_act.sa_handler = SIG_IGN;
	sigquit_act.sa_flags = 0;
	sigemptyset(&sigquit_act.sa_mask);
	sigaction(SIGQUIT, &sigquit_act, NULL);
}
