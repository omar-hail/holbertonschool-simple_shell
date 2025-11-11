# 🐚 C - Simple Shell

A collaborative project at **Holberton School** to build a simple UNIX command line interpreter in C, step by step:  
from running a single command, to handling `PATH`, built-ins like `exit` and `env`, and proper error handling.

---

## 📚 Table of Contents

- [Overview](#overview)
- [Features by Version](#features-by-version)
  - [0. README, man, AUTHORS](#0-readme-man-authors)
  - [1. Betty would be proud](#1-betty-would-be-proud)
  - [2. Simple shell 0.1](#2-simple-shell-01)
  - [3. Simple shell 0.2](#3-simple-shell-02)
  - [4. Simple shell 0.3](#4-simple-shell-03)
  - [5. Simple shell 0.4](#5-simple-shell-04)
  - [6. Simple shell 1.0](#6-simple-shell-10)
- [Requirements](#requirements)
- [Compilation](#compilation)
- [Usage](#usage)
  - [Interactive mode](#interactive-mode)
  - [Non-interactive mode](#non-interactive-mode)
- [Built-in Commands](#built-in-commands)
- [Environment Handling](#environment-handling)
- [Files](#files)
- [Team](#team)

---

## 🧠 Overview

This project re-implements a very simple version of a UNIX shell.

The shell:

- Displays a prompt
- Reads and parses user input
- Creates child processes with `fork`
- Replaces the child’s image with new programs using `execve`
- Handles `PATH` resolution
- Implements simple built-ins: `exit` and `env`
- Works both in interactive and non-interactive modes

The goal is to understand how a real shell like `/bin/sh` works internally.

---

## 🚀 Features by Version

### 0. README, man, AUTHORS

- `README.md` – Overall description of the project and usage.
- `man_1_simple_shell` – Manual page for the shell.
- `AUTHORS` – List of contributors to the repository.

---

### 1. Betty would be proud

- All C files follow **Betty style**:
  - Proper formatting, indentation, and documentation.
  - No more than 5 functions per file.
- Code passes:
  - `betty-style.pl`
  - `betty-doc.pl`

---

### 2. Simple shell 0.1

**Basic UNIX command line interpreter:**

- Displays a prompt and waits for the user to type a command.
- Each command line ends with a new line (Enter).
- After executing a command, the prompt is shown again.
- Commands are simple: **one word only** (no arguments).
- No `PATH` handling:
  - Commands must be given as full paths (e.g. `/bin/ls`, not `ls`).
- If the executable cannot be found:
  - Print an error message.
  - Show the prompt again.
- Handles **EOF** (Ctrl+D):
  - In interactive mode, exits cleanly when EOF is reached.
- Uses `execve` as the core call to run programs and passes `environ` to it.

---

### 3. Simple shell 0.2

**Extends 0.1 with arguments:**

- Command lines can contain a program **and arguments**:
  - Example: `ls -l /tmp`
- The input line is tokenized into:
  - `argv[0] = command`
  - `argv[1..n] = arguments`
- `execve` is called with the full `argv` array.

---

### 4. Simple shell 0.3

**Extends 0.2 with:**

- **PATH handling**:
  - If the command does not contain `/` (e.g. `ls`):
    - The shell searches for the executable in the directories listed in `PATH`.
    - Builds full paths like `/bin/ls`, `/usr/bin/ls`, etc.
    - Uses the first matching executable.
  - If the command contains `/` (e.g. `/bin/ls`, `./hbtn_ls`):
    - It is treated as a full or relative path and used as is.
- **No unnecessary forks**:
  - If the command does not exist (cannot be found or executed):
    - `fork` is **not** called.
    - An error is printed and the shell returns to the prompt.
  - When a command is not found, the shell returns status code `127`.

---

### 5. Simple shell 0.4

**Extends 0.3 with the `exit` built-in:**

- Implements a built-in command:

  ```sh
  exit
