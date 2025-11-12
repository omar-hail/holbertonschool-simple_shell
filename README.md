# 🐚 Simple Shell (`#cisfun$`)

> A minimal UNIX command interpreter written in **C**, developed as part of the **Holberton School – “The Gates of Shell”** project.  
> It provides a simple interactive interface to execute commands, manage environment variables, and exit gracefully.

---

## 🧠 Description

**simple_shell** is a basic UNIX command line interpreter.  
It reads user input, parses commands, and executes them either directly or by searching the system `PATH`.  
It supports both **interactive** and **non-interactive** modes.

**Key behaviors:**
- Uses `getline()` to read input dynamically.
- Trims leading and trailing spaces or tabs.
- Handles built-in commands (`exit`, `env`).
- Manually searches for executables using the `PATH` environment variable.
- Returns proper exit statuses and handles **EOF (Ctrl+D)** gracefully.

---

## 🧩 Features

✅ **Custom prompt:**  
#cisfun$
✅ **Supports both modes:**
- **Interactive:** user types commands directly in the shell.
- **Non-interactive:** commands are piped from a file or another program.

✅ **Built-in commands:**

| Command | Description |
|----------|-------------|
| `exit` | Terminates the shell (status 0). |
| `env` | Prints all environment variables. |

✅ **Command execution:**
- Reads input with `getline()`.
- Removes extra whitespace.
- Searches for executables within directories in `$PATH` using `access()`.
- Executes valid commands with `fork()` and `execve()`.
- Returns the exit status of the last executed command.

✅ **Error handling:**
- Displays clear error messages when commands fail.
- Handles **Ctrl+D** safely in interactive mode.

---

## ⚙️ Usage

### 🧍 Interactive mode
```bash
$ ./hsh
#cisfun$ env
PATH=/usr/local/bin:/usr/bin:/bin
PWD=/home/user/simple_shell
#cisfun$ exit
$
```
🔁 Non-interactive mode
```
$ echo "env" | ./hsh
PATH=/usr/local/bin:/usr/bin:/bin
PWD=/home/user/simple_shell
```
🧱 EOF Handling

Press Ctrl+D to exit gracefully:
```
#cisfun$ <Ctrl+D>
$
```
🧠 Flow of Execution
```
Start
 └──► main.c → calls shell_loop()
        ├──► Displays prompt (#cisfun$)
        ├──► Reads input via getline()
        ├──► Trims spaces/tabs
        ├──► Checks for built-ins (exit, env)
        ├──► If not built-in → searches PATH
        ├──► Executes using fork() + execve()
        └──► Repeats until 'exit' or EOF
```
📂 File Structure
File	Description
main.c	Entry point of the program; calls the main shell loop.
loop.c	Contains shell_loop() and input trimming functions.
builtin.c	Implements built-in commands (exit, env).
exec.c	Handles PATH searching and command execution.
shell.h	Header file with prototypes and global variables.

🧩 Compilation

Compile the program using:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
🧪 Testing
Interactive mode:
```
./hsh
#cisfun$ env
#cisfun$ exit
```
Non-interactive mode:
```
echo "env" | ./hsh
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

write()

getline()

strcmp(), strlen(), strcpy()

malloc(), free()

access()

isatty()

exit()

environ (global variable)

📄 Requirements

Operating System: Ubuntu 20.04 LTS

Compiler: gcc

Flags:
```
-Wall -Werror -Wextra -pedantic -std=gnu89
```
Follow Betty coding style.

No memory leaks.

Maximum of 5 functions per file.

All header files must be include-guarded.

