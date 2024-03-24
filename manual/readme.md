MyShell(1)                            General Commands Manual                            MyShell(1)

NAME
       MyShell - My Shell

SYNOPSIS
       myshell [batch_file]

DESCRIPTION
       myshell is a simple shell program that provides a basic command-line interface for
       interacting with the operating system. It supports executing commands,
       navigating directories, managing environment variables, and handling signals.
       The design and implementation of MyShell are based on established principles and
       techniques in shell programming and operating system interaction (Cooper 2004; Robbins 2005).

OPTIONS
       batch_file
              If specified, myshell operates in batch mode, reading commands from the
              specified file instead of interactively from the user.

COMMANDS
       cd [directory]
              Change the current working directory to the specified directory. If no
              directory is provided, cd changes to the home directory. This command
              leverages the UNIX philosophy of simplicity and modularity (Raymond 2003).

       clr    Clear the screen.

       dir [directory]
              List the contents of the specified directory. If no directory is
              provided, dir lists the contents of the current directory.

       environ
              List all environment strings, showcasing the shell's capability to manage
              and display operating system environments (Peek et al. 2002).

       echo [text ...]
              Display the specified text.

       help   Display the user manual using the more filter.

       pause  Pause the shell until the user presses Enter.

       quit   Exit the shell.

SIGNAL HANDLING
       SIGINT (Ctrl+C)
              Terminate the currently running foreground process, if any. This signal
              handling is vital for process control in interactive shell environments
              (Stevens & Rago 2013).

       SIGQUIT (Ctrl+D)
              Exit the shell.

AUTHOR
       This shell was created by Ayden Jahola.

REFERENCES
       Cooper, M. (2004). 'Advanced Programming in the UNIX Environment'. Addison-Wesley Professional.

       Peek, J., O'Reilly, T., & Loukides, M. (2002). 'UNIX Power Tools'. O'Reilly Media.

       Raymond, E.S. (2003). 'The Art of UNIX Programming'. Addison-Wesley Professional.

       Robbins, A. (2005). 'UNIX in a Nutshell: A Desktop Quick Reference for SVR4 and Solaris 7'.
       O'Reilly Media.

       Stevens, W.R., & Rago, S.A. (2013). 'Advanced Programming in the UNIX Environment, Third Edition'.
       Addison-Wesley Professional.

