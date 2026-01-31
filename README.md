*This project has been created as part of the 42 curriculum by pcaplat.*

# Pipex

## Description

**Pipex** is a project from the 42 curriculum whose goal is to reproduce the behavior of Unix pipes in a simplified way.

The program mimics how a shell executes commands connected by the pipe (`|`) operator, redirecting the output of one command to the input of the next one.

Through this project, several fundamental concepts of Unix system programming are explored:

- Process creation using fork

- Inter-process communication with pipe

- File descriptor duplication with dup2

- Command execution using execve

- Input and output redirections

- Command path resolution using the PATH environment variable

- Proper error handling and memory management

Pipex helps to better understand how a shell works internally and how Unix manages processes and file descriptors.

## Instructions

### Mandatory Part

To compile the mandatory part of the project :
```bash
make
```

To recompile the mandatory part from scratch :
```bash
make re
```

These commands will genereate an executable named pipex.

#### Usage

```bash
./pipex infile cmd1 cmd2 outfile
```
***Exemple:***
```bash
./pipex test "grep ai" "wc -l" out
```

Should acting in the same way than bash :
```bash
< test grep ai | wc -l > out
```

### Bonus Part


To compile the bonus part of this project :
```bash
make bonus
```

To recompile everything from scratch with bonuses :
```bash
make re_bonus
```

These command will genereate an executable named pipex.

#### Usage

The bonus part extends the mandatory program to behave even closer to a real shell.
The bonus features include :

- Handling mutiple pipes
```bash
./pipex infile cmd1 cmd2 ... cmdn outfile
```
- Handling here_doc
```bash
./pipex here_doc LIMITER cmd1 cmd2 outfile
```
Witch is equivalent to :
```bash
<< LIMITER cmd1 | cmd2 >> outfile
```
When using **here_doc**, the output is *appended* (>>) to outfile instead of being overwritten.

### Cleaning the project

To remove object files :
```bash
make clean
```

To remove object files and the executable : 
```bash
make fclean
```

## Resources

Here are some useful resources used during the developpement of this project:
- man **fork**
- man **pipe**
- man **dup2**
- man **execve**
- man **wait**
- [redirection documentation](https://www.pierre-giraud.com/shell-bash/redirection-gestion-flux/)
- [GNU redirection documentation](https://www.gnu.org/software/bash/manual/html_node/Redirections.html)

