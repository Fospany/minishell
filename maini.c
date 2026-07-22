/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maini.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 11:38:45 by dabdulla          #+#    #+#             */
/*   Updated: 2026/07/03 14:02:59 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int main()
// {
// 	char *path;
// 	char *str;
// 	char **av;
// 	char  *tmp;
// 	extern char **environ;
// 	pid_t pid;

// 	path = "/bin/";
// 	tmp = path;
// 	while ((str = readline("vibeshell: ")))
// 	{
// 		av = split_read_line(str);
// 		tmp = ft_strjoin(path, av[0]);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			execve(tmp, av, environ);
// 			perror("execve");
// 			exit(1);
// 		}
// 		waitpid(pid, NULL, 0);
// 		//free arguments of av
// 	}
// 	if (!path)
// 		return 0;
//     if (minishell("lofasz$$$festek"))
//         return (1);
//     return (0);
//
