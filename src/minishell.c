/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2023/12/22 16:01:18 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_env()
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		ft_putendl(environ[i]);
		i++;
	}
}

char	*read_command()
{

	char	*command;

	command = readline("minishell$ ");
	return (command);
}

char	**parse_command(char *command)
{
	char	**args;

	args = ft_split(command, ' ');
	return (args);
}

int execute_command(char **args)
{
	pid_t	pid;
	char	**environ;
	int		status;

	pid = fork();

	if (pid == 0) {

		if (execve(args[0], args, environ) == -1) {
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			waitpid(pid, &status, WUNTRACED);
		}
	}
	return (1);
}

int main(void)
{
	char	*command;
	char	**args;
	int		status;

	ft_init_env();
	while (1)
	{
		command = read_command();
		args = parse_command(command);
		status = execute_command(args);

		free(command);
		free(args);
	}
	return (0);
}