/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2023/12/09 12:54:01 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path)
{
	return chdir(path);
}

char **get_input(char *input)
{
	char **command = malloc(8 * sizeof(char *));
	char *separator = " ";
	char *parsed;
	int index = 0;

	parsed = strtok(input, separator);
	while (parsed != NULL) {
		command[index] = parsed;
		index++;
		parsed = strtok(NULL, separator);
	}

	command[index] = NULL;
	return command;
}

int main()
{
	char **command;
	char *input;
	pid_t child_pid;
	int stat_loc;

	while (1) {
		input = readline("unixsh> ");
		command = get_input(input);
		if (ft_strcmp(command[0], "cd") == 0)
		{
            if (cd(command[1]) < 0)
                perror(command[1]);
            continue;
        }
		if (!command[0])
		{
			free(input);child_pid = fork();
			free(command);
			continue;
		}
		child_pid = fork();
		if (child_pid < 0) {
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0) {
			execvp(command[0], command);
			if (execvp(command[0], command) < 0)
			{
				perror(command[0]);
				exit(1);
			}
			printf("This won't be printed if execvp is successul\n");
		}
		else
			waitpid(child_pid, &stat_loc, WUNTRACED);
		free(input);
		free(command);
	}
	return 0;
}
