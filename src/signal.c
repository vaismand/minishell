/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:21:45 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 09:48:41 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// handles the signal
void sigint_handler(int signo) 
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		// Let readline know that we've moved to a new line
		rl_on_new_line();
		// Clear the current input line in readline
		rl_replace_line("", 0);
		// Redisplay the prompt on a new line
		rl_redisplay();

	}
}

void set_signals(void)
{
	struct sigaction sigint_act;
	struct sigaction sigquit_act;
	// Setting up the SIGINT handler
	sigint_act.sa_handler = sigint_handler;
	sigint_act.sa_flags = SA_RESTART;
	sigemptyset(&sigint_act.sa_mask);
	sigemptyset(&sigquit_act.sa_mask);
	sigaddset(&sigint_act.sa_mask, SIGINT);
	sigaction(SIGINT, &sigint_act, NULL);
	// Setting up SIGQUIT to be ignored
	sigquit_act.sa_handler = SIG_IGN; // SIG_IGN to ignore the signal
	sigaction(SIGQUIT, &sigquit_act, NULL);
}