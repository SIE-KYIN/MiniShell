/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:06:25 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 10:50:24 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_command(t_tree_node *root, t_list *env)
{
	int	pid;
	int	status;
	int	ret;

	if (execute_builtin(root->command, env) == 0)
		return (0);
	pid = fork();
	if (pid == -1)
		printf("FORK ERROR\n");
	else if (pid == 0)
	{
		ret = execute_nonbuiltin(root->command, env);
		strerror(errno);
		exit(errno);
	}
	else
	{
		set_signal();
		pid = wait(&status);
		set_status(env, get_status(status));
	}
	return (0);
}

int	execute_builtin(char **arg, t_list *env)
{
	int	ret;

	if (ft_strcmp("echo", arg[0]) == 0)
		ret = ft_echo(arg);
	else if (ft_strcmp("cd", arg[0]) == 0)
		ret = ft_cd(arg, env);
	else if (ft_strcmp("pwd", arg[0]) == 0)
		ret = ft_pwd();
	else if (ft_strcmp("export", arg[0]) == 0)
		ret = ft_export(arg, env);
	else if (ft_strcmp("unset", arg[0]) == 0)
		ret = ft_unset(arg, env);
	else if (ft_strcmp("env", arg[0]) == 0)
		ret = ft_env(env);
	else if (ft_strcmp("exit", arg[0]) == 0)
		ret = ft_exit(arg, env);
	else
		return (-1);
	set_status(env, ret);
	return (0);
}

static int	add_path(char **arg, t_list *env, char **env_ptr)
{
	char	**path;
	char	*filepath;
	int		i;
	int		ret;

	path = ft_split(search_node(env, "PATH")->data, ':');
	i = -1;
	while (path[++i])
	{
		filepath = ft_strjoin_3(path[i], "/", arg[0]);
		ret = execve(filepath, arg, env_ptr);
		free(filepath);
	}
	ft_split_free(path);
	return (ret);
}

int	execute_nonbuiltin(char **arg, t_list *env)
{
	int		ret;
	char	**env_ptr;

	env_ptr = gather(env);
	ret = execve(arg[0], arg, env_ptr);
	if (search_node(env, "PATH"))
		ret = add_path(arg, env, env_ptr);
	if (ret != 0)
	{
		strerror(errno);
		printf("minishell: %s: command not found\n", arg[0]);
	}
	return (1);
}
