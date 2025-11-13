# 🐚 Simple Shell (`#cisfun$`)

> A lightweight UNIX command interpreter written in **C**, developed as part of the **Holberton School – “The Gates of Shell”** project.  
> This shell provides a clean interactive interface to execute programs, handle environment variables, and exit smoothly.

---

## 🧠 Description

**simple_shell** is a minimal command-line interpreter.  
It reads user input, parses the command, resolves its executable (either by absolute path or through `$PATH`), and runs it in a child process.

It works in **interactive** and **non-interactive** modes while respecting all project constraints and the Betty coding style.

**Core behaviors:**

- Uses `getline()` to read commands.
- Supports commands with or without arguments.
- Handles built-ins (`exit`, `env`).
- Searches for executables manually using `$PATH`.
- Executes valid programs using `fork()` + `execve()`.
- Returns accurate exit statuses.
- Handles **EOF (Ctrl+D)** gracefully.
- Works in both **pipe mode** and **terminal mode**.

---

## 🧩 Features

### 🚀 Prompt
Custom prompt displayed in interactive mode:

#cisfun$

### 🔀 Modes supported
✔ **Interactive:** User types directly into the shell.  
✔ **Non-interactive:** Commands received through pipes or files.

### 🔧 Built-in commands

| Command | Description |
|--------|-------------|
| `exit` | Exits the shell. |
| `env`  | Prints all environment variables. |

### ⚙️ Command execution
- Reads input with `getline()`.
- Tokenizes command + arguments.
- Removes extra whitespace.
- Resolves binary paths using the directories inside `$PATH`.
- Checks file accessibility with `access()`.
- Executes via `fork()` and `execve()`.
- Waits for child process using `wait()`.

### 🛡 Error handling
- Prints clear error messages in the exact required format:
./hsh: 1: command: not found
- Handles invalid commands.
- Detects EOF and exits cleanly.

---

## ⚙️ Usage

### 🧍 Interactive mode
```bash
$ ./hsh
#cisfun$ /bin/ls
#cisfun$ env
#cisfun$ exit
$
```
🔁 Non-interactive mode
```
$ echo "env" | ./hsh
PATH=/usr/bin:/bin
PWD=/home/user/simple_shell
```
⛔ EOF Handling

Press Ctrl+D to exit:
```
#cisfun$ <Ctrl+D>
$
```
🧠 Flow of Execution
```
Start
 └──► main.c → shell_loop()
        ├──► show prompt (#cisfun$)
        ├──► getline() input
        ├──► trim + tokenize
        ├──► check built-ins (exit, env)
        ├──► resolve command path
        ├──► fork() + execve()
        ├──► wait() for child
        └──► repeat until "exit" or EOF
```
📁 File Structure

| File               | Description                                   |
| ------------------ | --------------------------------------------- |
| **main.c**         | Entry point; starts the shell loop.           |
| **loop.c**         | Implements `shell_loop()` and input handling. |
| **tokenizer.c**    | Splits input into arguments.                  |
| **executor.c**     | Handles forking, execve, and exit status.     |
| **path.c**         | Resolves commands using `$PATH`.              |
| **builtins.c**     | Implements built-ins (`exit`, `env`).         |
| **env_utils.c**    | Helpers for environment variables.            |
| **string_utils.c** | Helper string functions.                      |
| **errors.c**       | Formats and prints error messages.            |
| **shell.h**        | Header file with prototypes & globals.        |
| **AUTHORS**        | List of project contributors.                 |

🧩 Compilation
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
🧪 Testing
Interactive:
```
./hsh
#cisfun$ ls
#cisfun$ exit
```
Non-interactive:
```
echo "ls" | ./hsh
```
⚡️ Example Session
```
$ ./hsh
#cisfun$ env
USER=user
PATH=/usr/bin:/bin
PWD=/home/user/simple_shell
#cisfun$ exit
$
```
🧰 System Calls & Functions Used

- write()

- getline()

- malloc(), free()

- fork(), execve(), wait()

- access()

- isatty()

- stat()

- strtok()

- strcmp(), strlen()

- environ (global variable)

📄 Requirements

- Ubuntu 20.04 LTS

- gcc with:
```
-Wall -Werror -Wextra -pedantic -std=gnu89
```
- Betty style compliance

- No memory leaks

- Maximum 5 functions per file

- Header files must be include-guarded

💬 Conclusion

The Simple Shell project demonstrates how UNIX shells operate behind the scenes.
It processes user commands, manages processes, handles environment variables, and mimics the behavior of traditional shells.

A clean, foundational project for understanding system programming,
process control, and UNIX internals — all written in pure C. 🚀
