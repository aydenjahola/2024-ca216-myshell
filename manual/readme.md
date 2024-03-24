MyShell/ash(1)                            General Commands Manual                            MyShell/ash(1)

NAME
       MyShell/ash - Ayden's SHell

SYNOPSIS
       myshell [command | file]

DESCRIPTION
       ash is a simple shell program that provides a basic command-line interface for
       interacting with the operating system. It supports executing commands,
       navigating directories, managing environment variables, and handling signals.
       The design and implementation of MyShell are based on established principles and
       techniques in shell programming and operating system interaction (Cooper 2004; Robbins 2005).

OPTIONS
       batch_file
              If specified, ash operates in batch mode, reading commands from the
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

ENVIRONMENT VARIABLES
        Environment variables are key-value pairs that are used by the shell and other 
        programs to retrieve information about the environment the shell operates in. 
        ash allows users to view and set environment variables, affecting the execution 
        of programs and scripts. For example, the PATH variable dictates the directories in 
        which the shell looks for executables.

I/O REDIRECTION
        MyShell supports basic input/output redirection, enabling users to redirect the input 
        and output of commands to files or from one command to another:

        > filename      Redirects the output of a command to a file, overwriting the existing contents.
        < filename      Takes the input for a command from a file.
        >> filename     Redirects the output of a command to a file, appending to its existing contents.

PROCESS CONCEPT
        ash can execute commands as either foreground or background processes:

        Foreground execution: The shell waits for the command to complete before accepting new input.
        Background execution: By appending & to a command, it is executed in the background, allowing the shell to accept new commands immediately.

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

STATEMENT OF NON-PLAGIARISM
    I hereby declare that I have written this submission and that it is all my own work. 
    I understand that my work may be checked for plagiarism and 
    that I would be penalized if it is found to be plagiarized.

    I understand that the University regards breaches of academic integrity and plagiarism as grave and serious. 
    I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be 
    imposed should I engage in practice or practices that breach this policy.

    - Student Number: 22406966
    - Student Name: Ayden Jahola
    - Date: 24/03/2024
