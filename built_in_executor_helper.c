#include "minishell.h"

int	restore_io(int saved_stdin, int saved_stdout)
{
	int	return_value;

	return_value = 0;
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		return_value = 1;
		perror("minishell");
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		return_value = 1;
		perror("minishell");
	}
	close(saved_stdin);
	close(saved_stdout);
	return (return_value);
}
