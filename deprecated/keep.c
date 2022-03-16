int		pipex(char **argv, char **envp, t_pipex *env)
{
	env->cmd[0].cmd = find_cmd_path(argv[2], envp, env, 0);
	env->cmd[0].args = ft_split(argv[2], ' ');
	env->cmd[1].cmd = find_cmd_path(argv[3], envp, env, 1);
	env->cmd[1].args = ft_split(argv[3], ' ');	
	pipe(env->pipe);
	env->pid1 = fork();
	if (env->pid1 < 0)
		free_all(env, "Forking failed.");
	else if (env->pid1 == 0)
		child(env->fdin, env->pipe[1], env->cmd[0].cmd, env->cmd[0].args, envp);
	else if (env->pid1 > 0)
	{
		wait(NULL);
		close(env->pipe[1]);
		env->pid2 = fork();
		if (env->pid2 < 0)
			free_all(env, "Forking failed.");
		else if (env->pid2 == 0)
			child(env->pipe[0], env->fdout, env->cmd[1].cmd, env->cmd[1].args, envp);
		else if (env->pid2 > 0)
			wait(NULL);
		close_fd(*env);
	}
	return (0);
}

char	*find_cmd_path(char *cmd, char **envp, t_pipex *env, int cmdnbr)
{
	int	i;

	i = 0;
	get_paths("PATH", envp, env);
	env->cmd[cmdnbr].args = ft_split(cmd, ' ');
	if (!env->cmd[cmdnbr].args)
		exit_env_clean("Error. Failed to parse user command input.", env);
	while (env->paths[i])
	{
		env->tmp_path = ft_strjoin(env->paths[i], env->cmd[cmdnbr].args[0]);
		if (!env->tmp_path)
			exit_env_clean("Error. strjoin() failed.", env);
		else if (!access(env->tmp_path, F_OK))
		{
			find_cmd_path_cleaner(env);
			return (env->tmp_path);
		}
		free (env->tmp_path);
		ft_memset(env->tmp_path, 0, ft_strlen(env->tmp_path));
		i++;
	}
	find_cmd_path_cleaner(env);
	exit (1);
}