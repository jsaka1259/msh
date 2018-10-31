===> msh_echo_test <===
<msh_echo_test case: 0> SUCCESS
in : argc     = 0
ex : ret      = 0
     out      = 
"
"
out: ret      = 0
     out      = 
"
"
<msh_echo_test case: 1> SUCCESS
in : argc     = 1
     argv[ 0] = "echo"
ex : ret      = 0
     out      = 
"
"
out: ret      = 0
     out      = 
"
"
<msh_echo_test case: 2> SUCCESS
in : argc     = 2
     argv[ 0] = "echo"
     argv[ 1] = "abc"
ex : ret      = 0
     out      = 
"abc
"
out: ret      = 0
     out      = 
"abc
"
<msh_echo_test case: 3> SUCCESS
in : argc     = 3
     argv[ 0] = "echo"
     argv[ 1] = "abc"
     argv[ 2] = "def"
ex : ret      = 0
     out      = 
"abc def
"
out: ret      = 0
     out      = 
"abc def
"
>>>> SUCCESS <<<<

===> msh_exit_test <===
<msh_exit_test case: 0> SUCCESS
in : argc     = 0
ex : ret      = 0
out: ret      = 0
<msh_exit_test case: 1> SUCCESS
in : argc     = 1
     argv[ 0] = "exit"
ex : ret      = 0
out: ret      = 0
<msh_exit_test case: 2> SUCCESS
in : argc     = 2
     argv[ 0] = "exit"
     argv[ 1] = "0"
ex : ret      = 0
out: ret      = 0
<msh_exit_test case: 3> SUCCESS
in : argc     = 2
     argv[ 0] = "exit"
     argv[ 1] = "1"
ex : ret      = 1
out: ret      = 1
<msh_exit_test case: 4> SUCCESS
in : argc     = 2
     argv[ 0] = "exit"
     argv[ 1] = "-1"
ex : ret      = -1
out: ret      = -1
>>>> SUCCESS <<<<

===> msh_help_test <===
<msh_help_test case: 0> FAILURE
in : argc     = 0
ex : ret      = 0
     out      = 
"echo [arg ...]
exit [n]
help [pattern ...]
"
out: ret      = 0
     out      = 
"
exit [n]
help [pattern ...]
"
<msh_help_test case: 1> SUCCESS
in : argc     = 1
     argv[ 0] = "help"
ex : ret      = 0
     out      = 
"echo [arg ...]
exit [n]
help [pattern ...]
"
out: ret      = 0
     out      = 
"echo [arg ...]
exit [n]
help [pattern ...]
"
<msh_help_test case: 2> SUCCESS
in : argc     = 2
     argv[ 0] = "help"
     argv[ 1] = "echo"
ex : ret      = 0
     out      = 
"echo: echo [arg ...]
    Write arguments to the standard output.

    Display the ARGs, separated by a single space character and followed by a
    newline, on the standard output.
"
out: ret      = 0
     out      = 
"echo: echo [arg ...]
    Write arguments to the standard output.

    Display the ARGs, separated by a single space character and followed by a
    newline, on the standard output.
"
<msh_help_test case: 3> SUCCESS
in : argc     = 2
     argv[ 0] = "help"
     argv[ 1] = "exit"
ex : ret      = 0
     out      = 
"exit: exit [n]
    Exit the shell.

    Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
"
out: ret      = 0
     out      = 
"exit: exit [n]
    Exit the shell.

    Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
"
<msh_help_test case: 4> SUCCESS
in : argc     = 2
     argv[ 0] = "help"
     argv[ 1] = "help"
ex : ret      = 0
     out      = 
"help: help [pattern ...]
    Display information about builtin commands.

    Displays brief summaries of builtin commands.  If PATTERN is
    specified, gives detailed help on all commands matching PATTERN,
    otherwise the list of help topics is printed.

    Arguments:
      PATTERN	Pattern specifiying a help topic
"
out: ret      = 0
     out      = 
"help: help [pattern ...]
    Display information about builtin commands.

    Displays brief summaries of builtin commands.  If PATTERN is
    specified, gives detailed help on all commands matching PATTERN,
    otherwise the list of help topics is printed.

    Arguments:
      PATTERN	Pattern specifiying a help topic
"
<msh_help_test case: 5> SUCCESS
in : argc     = 4
     argv[ 0] = "help"
     argv[ 1] = "echo"
     argv[ 2] = "exit"
     argv[ 3] = "help"
ex : ret      = 0
     out      = 
"echo: echo [arg ...]
    Write arguments to the standard output.

    Display the ARGs, separated by a single space character and followed by a
    newline, on the standard output.
exit: exit [n]
    Exit the shell.

    Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
help: help [pattern ...]
    Display information about builtin commands.

    Displays brief summaries of builtin commands.  If PATTERN is
    specified, gives detailed help on all commands matching PATTERN,
    otherwise the list of help topics is printed.

    Arguments:
      PATTERN	Pattern specifiying a help topic
"
out: ret      = 0
     out      = 
"echo: echo [arg ...]
    Write arguments to the standard output.

    Display the ARGs, separated by a single space character and followed by a
    newline, on the standard output.
exit: exit [n]
    Exit the shell.

    Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
help: help [pattern ...]
    Display information about builtin commands.

    Displays brief summaries of builtin commands.  If PATTERN is
    specified, gives detailed help on all commands matching PATTERN,
    otherwise the list of help topics is printed.

    Arguments:
      PATTERN	Pattern specifiying a help topic
"
>>>> FAILURE <<<<

FAILURE [1]
