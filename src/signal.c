/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:21:45 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/07 21:21:45 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handles the signal
static void sigint_handler(int signo) 
{
	(void)signo;  // To avoid unused variable warning
	// Simply move to a new line and print the prompt
	printf("\n");
	printf("supershell$ ");
	fflush(stdout); // Ensure the prompt is displayed immediately
}

void set_signals(void)
{
	struct sigaction sigint_act;
	struct sigaction sigquit_act;

	// Setting up the SIGINT handler
	sigint_act.sa_handler = sigint_handler;
	sigint_act.sa_flags = SA_RESTART;
	sigemptyset(&sigint_act.sa_mask);
	sigaddset(&sigint_act.sa_mask, SIGINT);
	sigaction(SIGINT, &sigint_act, NULL);
	// Setting up SIGQUIT to be ignored
	sigquit_act.sa_handler = SIG_IGN; // SIG_IGN to ignore the signal
	sigaction(SIGQUIT, &sigquit_act, NULL);
}