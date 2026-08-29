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

delete maini.c

Problems, tests and TO-DOs

- [ ] 2: Syntax error should set the exitcode to 2
- [x] 127: Command not found (or no such file or directory) 
- [x] 126: Permission denied (or is a directory) 
- [x] 130: Killed by sigint 
- [x] 131: killed by sigquit
- [ ] need to handle expansions in heredoc
- [ ] properly handle $EMPTY_VAR
- [ ] test heredoc with quotes and everything
- [ ] finish built-ins
- [ ] handle $?
- [ ] valgrind/funcheck
- [ ] run testers
- [ ] cleanup the directoryies and check for leftover files

---

things to do after everything is fixed

- [ ] finish readme
- [ ] norminette
- [ ] unused function check
- [ ] unused headers check
