/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/02 16:29:07 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putendl(char *s)
{
	ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}

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
	extern char	**environ;
	int		status;

	pid = fork();
	if (pid == 0) {

		if (execve(args[0], args, environ) == -1)
		{
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

	(void)status;
	//ft_init_env();
	while (1)
	{
		command = read_command();
		args = parse_command(command);
		execute_command(args);
		free(command);
		free(args);
	}
	return (0);
}