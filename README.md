# Minishell - 42 Berlin

## Introduction
Minishell is a simplified shell project developed at 42 Berlin. The goal is to create a basic command-line interpreter that mimics the behavior of Bash, handling user input, executing commands, managing processes, and handling redirections and pipelines. This project helps deepen understanding of system calls, process management, and file descriptors in Unix-based operating systems.

## Features
- Command execution (similar to Bash)
- Handling of built-in commands (e.g., `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- Support for pipes (`|`) and redirections (`>`, `>>`, `<`)
- Environment variable management
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Proper error handling and memory management

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/emily-cloud/42-minishell.git
   cd minishell
   ```
2. Compile the project:
   ```sh
   make
   ```
3. Run Minishell:
   ```sh
   ./minishell
   ```

## Built-in Commands
- `echo` - Prints arguments to the terminal.
- `cd` - Changes the current working directory.
- `pwd` - Prints the current directory.
- `export` - Sets environment variables.
- `unset` - Unsets environment variables.
- `env` - Prints the environment variables.
- `exit` - Exits the shell.

## Usage Examples
- Running a simple command:
  ```sh
  ls -la
  ```
- Using pipes:
  ```sh
  ls | grep minishell
  ```
- Redirection:
  ```sh
  echo "Hello" > file.txt
  cat < file.txt
  ```

## Signals Handling
- `Ctrl+C` - Interrupts the current process.
- `Ctrl+D` - Exits the shell.
- `Ctrl+\` - Quits the process.

## Code Structure
- `src/` - Contains the main source code.
- `includes/` - Header files.
- `Makefile` - Compilation rules.

## Authors
Developed as part of 42 Berlin's curriculum by [Huayun Ai  / Rufussed ].

