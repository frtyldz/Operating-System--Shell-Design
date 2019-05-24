# Linux Shell in C

To know more about what a shell is, click here.

We all use the built in terminal window in Linux distributions like Ubuntu, Fedora, etc. But how do they actually work? In this article, We are going to handle some under the hood features and algorithms what actually work inside a shell. All Linux operating systems have a terminal window to write in commands. But how are they executed properly after they are entered?
Also, how are extra features like keeping the history of commands and showing help handled? All of this can be understood by creating your own shell.



The Basics

After a command is entered, the following things are done:

Command is entered and if length is non-null, keep it in history.
Parsing : Parsing is the breaking up of commands into individual words and strings
Checking for special characters like pipes, etc is done
Checking if built-in commands are asked for.
If pipes are present, handling pipes.
Executing system commands and libraries by forking a child and calling execvp.
Printing current directory name and asking for next input.
