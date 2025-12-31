# 🐚 Minishell – 42 Berlin

Minishell is a student project from **42 Berlin** that recreates a simplified Unix shell.  
It teaches core system programming concepts such as **process creation**, **pipes**, **redirections**, **signal handling**, and **environment variable management**.

The goal is to implement essential shell behaviors described in the official subject, including command execution, quoting rules, PATH resolution, and built-in commands.

---

## 🌟 Features

### ✅ Mandatory Features
- Interactive **prompt**
- Working **command history**
- **Executable lookup** via `PATH`, absolute, or relative paths  
- **Quotes**  
  - `'single quotes'` preserve literal text  
  - `"double quotes"` allow variable expansion  
- **Environment variable expansion** (`$HOME`, `$USER`, `$?`, etc.)
- **Redirections**  
  - Input `<`  
  - Output `>`  
  - Append `>>`  
  - `<<` **heredoc** (delimiter required)
- **Pipes**: `cmd1 | cmd2 | cmd3`
- **Signals**  
  - `CTRL+C` → new prompt  
  - `CTRL+D` → exit shell  
  - `CTRL+\` → ignored
- Built-in commands:
  - `echo -n`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## ✨ Bonus Features  
(Only evaluated if mandatory is correct)

- Logical operators: `&&` and `||`
- Wildcard expansion: `*`
- Enhanced redirections
- Improved built-in robustness

---

## 🛠️ Installation

### macOS Preparation
```bash
brew install readline
```

Modify minishell.c:

```c
rl_clear_history();  replace with clear_history() on mac
```

### Clone & Build
```bash
git clone https://github.com/emily-cloud/42-minishell.git
cd 42-minishell
make
```

---

## ▶️ Usage

Start the shell:

```bash
./minishell
```

You can now:

- Execute commands (`ls`, `grep`, `cat`, `wc`, …)
- Use pipes:
  ```bash
  ls -l | grep .c
  ```
  
  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.30.42.png" width="75%">
  </p>

- Use redirections:
  ```bash
  echo hello > out.txt
  cat out.txt
  hello
  echo hey >> out.txt
  cat out.txt
  hello
  hey
  cat < out.txt
  hello
  hey
  ```

  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.34.23.png" width="75%">
  </p>
  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.35.57.png" width="75%">
  </p>


- Use heredocs:
  ```bash
  cat << EOF
  hello
  world
  EOF
  ```
  
  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.37.50.png" width="75%">
  </p>

- Manage environment variables:
  ```bash
  export NAME=Emily
  echo $NAME
  ```
  
  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.38.54.png" width="75%">
  </p>

- Pipes
   ```bash
  ls | grep c | wc -l
       2
  ls | grep c 
  screenshot
  src
  ```

  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.40.29.png" width="75%">
  </p>

- && ||
  ```bash
  ls && echo hello
  libft           minishell       obj             README.md       src
  Makefile        minishell_bonus out.txt         screenshot
  hello
  ls || echo hello
  libft           minishell       obj             README.md       src
  Makefile        minishell_bonus out.txt         screenshot
  ```

  <p align="center">
  <img src="https://github.com/emily-cloud/42-minishell/blob/main/screenshot/Screenshot%202025-12-31%20at%2016.41.48.png" width="75%">
  </p>


## 📚 Resources

- `man 3 readline`
- `man 2 fork`
- `man 2 execve`
- `man 2 pipe`
- `man 2 dup2`
- `man 2 waitpid`
- `man 2 signal`

---

## 👥 Authors

Developed for **42 Berlin** by:

- **Huayun Ai**  
- **Rufus Lane**

---

## 📄 License

This project is part of the **42 School curriculum** and follows its academic guidelines.

