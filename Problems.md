# Changes

Added this to *minishell* function:
```
if (*read_line == '\0')
	return (NULL);
```

This fixes a segfault, also it makes it possible when pressing enter, it just continues in new line.

added this to string_compare:
```
if (string1[i] == '\0' && string2[i] == '\0')
	return (1);
```
this fixed an issue where the > would only append >> so i added a check to see if its the correct size as well
