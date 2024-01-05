/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/05 13:04:05 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable for the signal
static volatile sig_atomic_t jump_active = 0;
static sigjmp_buf env;

int cd(char *path) {
    return chdir(path);
}

//creating a new list for every command
t_list	*new_lst(char *argv, char **envp)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		perror("malloc error");
	tmp->envp = envp;
	tmp->cmd = ft_split(argv, ' ');
	tmp->path = path_creator(tmp->cmd);
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->pd[0] = 0;
	tmp->pd[1] = 0;
	return (tmp);
}

//frees the paths array from path_finder
void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

//creates the path for the command
char	*path_creator(char **cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		perror("PATH not found");
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_paths(paths), NULL);
		path = ft_strjoin(tmp, cmd[0]);
		if (!path)
			return (free_paths(paths), free(tmp), NULL);
		free(tmp);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	free_paths(paths);
	return (path);
}

//initializes the struct
void	struct_init(t_list **pipex, char **envp, char *cmd)
{
	t_list	*tmp;
	char	*cmd;
	char	**argv;
	int 	i;

	i = -1;
	argv = ft_split(cmd, '|');
	while (argv[++i])
	{
		tmp = new_lst(argv[i], envp);
		if (!tmp)
			perror("malloc error");
		tmp->index = i;
		ft_lstadd_back(pipex, tmp);
	}
}

//redirects the output of the first command
void	first_child(t_list *pipex)
{
	dup2(pipex->pd[1], 1);
	close(pipex->pd[1]);
	close(pipex->pd[0]);
	while (pipex->next)
	{
		pipex = pipex->next;
		close(pipex->pd[0]);
		close(pipex->pd[1]);
	}
}

//redirects the input of the last command
void	last_child(t_list *pipex)
{
	dup2(pipex->prev->pd[0], 0);
	if (pipex->prev)
	{
		close(pipex->prev->pd[0]);
		close(pipex->prev->pd[1]);
	}
	while (pipex->prev)
	{
		close(pipex->pd[0]);
		close(pipex->pd[1]);
		pipex = pipex->prev;
	}
}

//redirects the input and output of the middle commands
void	middle_child(t_list *pipex)
{
	dup2(pipex->prev->pd[0], 0);
	dup2(pipex->pd[1], 1);
	while (pipex->prev)
	{
		close(pipex->pd[0]);
		close(pipex->pd[1]);
		pipex = pipex->prev;
	}
	while (pipex->next)
	{
		close(pipex->pd[0]);
		close(pipex->pd[1]);
		pipex = pipex->next;
	}
}
//redirects the input and output of the commands depending on their position
void	redirecting(t_list *pipex)
{
	if (pipex->prev == NULL && pipex->next == NULL)
		return ;
	else if (pipex->prev == NULL)
		first_child(pipex);
	else if (pipex->next == NULL)
		last_child(pipex);
	else
		middle_child(pipex);
}
// handles the signal
void sigint_handler(int signo) 
{
    if (!jump_active)
        return;
    siglongjmp(env, 42);
	(void)signo;
}

//executes the command
int execute_command(t_list *cmd_list)
{
	pid_t	pid;
	int		status;

	pipe(cmd_list->pd);
	pid = fork();
	if (pid == 0)
	{
		
		redirecting(cmd_list);
		execve(cmd_list->path, cmd_list->cmd, cmd_list->envp);
		perror("minishell");
		exit(EXIT_FAILURE);
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
		close(cmd_list->pd[1]); //dont forget to close the pipe
	}
	return (1);
}
//frees the list
void	freepipex(t_list *pipex)
{
	t_list	*tmp;

	while (pipex)
	{
		if (pipex->pd[0])
			close(pipex->pd[0]);
		if (pipex->pd[1])
			close(pipex->pd[1]);
		if (pipex->cmd)
		{
			pipex->index = 0;
			while (pipex->cmd[pipex->index])
				free(pipex->cmd[pipex->index++]);
			free(pipex->cmd);
		}
		if (pipex->path)
			free(pipex->path);
		tmp = pipex;
		pipex = pipex->next;
		free(tmp);
	}
}

int main(int ac, char **av, char **envp)
{
	int		status;
	char	*cmd;
	t_list	*cmd_list;
	// struct of signal
	struct sigaction sig;

    sig.sa_handler = sigint_handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sig, NULL);

	(void)ac;
	(void)av;
	(void)status;
	while (1)
	{
		// handle of CTRL+C
		if (sigsetjmp(env, 1) == 42)
		{
			printf("\n");
			continue;
		}
		jump_active = 1;
		cmd = ft_readline();
		struct_init(&cmd_list, envp, cmd);
		// should fix problem with empty command
		// if (cmd_list == NULL)
		// 	continue;

		// continue if the command is empty
		if (!cmd_list)
			continue;
		if (ft_strncmp(cmd_list->cmd[0], "NULL", 5) == 0)
		{
			printf("test\n");
			printf("\n");
			exit(0);
		}
		else if (ft_strncmp(cmd_list->cmd[0], "cd", 3) == 0)
			chdir(cmd_list->cmd[1]);
		else if (ft_strncmp(cmd_list->cmd[0], "exit", 5) == 0)
			exit(0);
		while (cmd_list)
		{
			execute_command(cmd_list);
			cmd_list = cmd_list->next;
		}
		freepipex(cmd_list);
	}
	return (0);
}