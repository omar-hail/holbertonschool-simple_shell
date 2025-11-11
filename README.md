# 🐚 C - Simple Shell

A collaborative project at **Holberton School** to build a simple UNIX command line interpreter in C.

This README gives a **high-level overview** of the project.  
All detailed behavior, options, and examples are documented in the man page (`man_1_simple_shell`).

---

## 🧠 Project Overview

The goal of this project is to re-create a very simple version of a UNIX shell, similar to `/bin/sh`, and in the process learn how:

- Processes are created (`fork`)
- Programs are executed (`execve`)
- The environment and `PATH` work
- A command-line interface (CLI) loop is built

The shell:

- Displays a prompt
- Reads user input
- Parses commands and their arguments
- Locates executables (using `PATH` or full paths)
- Executes commands in child processes
- Implements basic built-in commands

---

## 🚀 Implemented Features

Over several tasks, the shell grows from a minimal interpreter to a more complete simple shell:

- **Basic command execution**
  - Displays a prompt and waits for user input
  - Executes commands given as full paths (e.g. `/bin/ls`)
  - Handles end-of-file (EOF / Ctrl+D) and returns to the terminal cleanly

- **Arguments support**
  - Parses a command line into a program name and arguments  
    (e.g. `ls -l /tmp`)

- **PATH handling**
  - If the command does not contain `/`, the shell searches for it in the directories listed in `PATH`
  - Uses the first executable found
  - If the command cannot be found, it prints an error and returns status `127`
  - `fork` is not called if the command does not exist

- **Built-ins**
  - `exit`  
    Exits the shell cleanly (no argument handling required)
  - `env`  
    Prints the current environment variables

- **Interactive and non-interactive modes**
  - Interactive: user types commands at a prompt
  - Non-interactive: commands can be piped from a file or another program  
    (e.g. `echo "/bin/ls" | ./hsh`)

---

## 📋 Requirements (Summary)

- Language: **C**
- OS: **Ubuntu 20.04 LTS**
- Compiler flags:
  ```sh
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89
