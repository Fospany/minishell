# Known Problems / Changes I've made

Added this to *minishell* function:
```
if (*read_line == '\0')
	return (NULL);
```
This fixes a segfault, also it makes it possible when pressing enter, it just continues in new line.
