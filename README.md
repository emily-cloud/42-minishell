# Minishell - 42 Berlin

## Introduction
Minishell is a student project at 42 Berlin that aims to create a simple shell program similar to Bash. It allows users to execute commands, handle input/output redirections, and manage processes. This project helps students understand Unix processes, system calls, and file descriptors.

## Features
### Mandatory
- Command execution using `fork`, `execve`, `waitpid`, `pipe`, etc.
- Basic built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Input/output redirections: `>`, `>>`, `<`.
- Pipes (`|`) for command chaining.
- Environment variable management.
- Handling of signals (`CTRL+C`, `CTRL+D`, `CTRL+\`).
- Error handling and proper memory management.

### Bonus Features
- Support for `&&` and `||` logical operators.
- Wildcard expansion (`*` matching files in directories).
- Advanced redirections and file descriptor handling.
- More built-in commands for an enhanced shell experience.
- `heredoc` (`<<`) implementation.
- Improved signal handling and job control.

## Installation
```bash
git clone  git clone https://github.com/emily-cloud/42-minishell.git
cd minishell
make
```

## Usage
```bash
./minishell
```
- Run commands just like in Bash.
- Use built-in commands for directory and environment management.

## Authors
- Developed as part of the 42 Berlin curriculum.

## Resources
- `man 3 readline`
- `man 2 fork`
- `man 2 execve`
- `man 2 pipe`
- `man 2 dup2`
- `man 2 waitpid`
- `man 2 signal`

## License
This project is part of the 42 curriculum and follows its academic guidelines.

## Authors
Developed as part of 42 Berlin's curriculum by [Huayun Ai  / Rufussed ].

