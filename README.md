# Minishell 🐚
 
**Minishell** is a minimalistic shell implementation in C, built to replicate many features of a standard UNIX shell. This project offers hands-on experience with process creation, signal handling, file redirection, and other essential shell operations. 

## Table of Contents

- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Installation](#installation)
- [Usage](#usage)
- [Shell Commands Supported](#shell-commands-supported)
- [Author](#author)

## Project Overview

As part of the [42 School](https://42.fr/) curriculum, **Minishell** introduces the core concepts behind UNIX-like shells. It is designed to run in a terminal environment and interpret user commands, manage processes, and handle I/O redirection.

The project challenges are:
- Manage processes (using `fork`, `exec`, and `wait`).
- Parse and interpret user input.
- Implement built-in shell commands.
- Handle signals for job control (like `CTRL-C`, `CTRL-D`, and `CTRL-\`).

## Key Features

**Minishell** includes:
- Basic command execution with path resolution.
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Single and double quotes handling to parse complex command structures.
- Environment variable expansion.
- Basic redirections (`<`, `>`, `>>`) and pipes (`|`).
- Here-document (`<<`) support for multi-line input.
- Signal handling for interactive input (e.g., handling `CTRL+C`).

## Installation

To set up **Minishell**, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/asut00/minishell.git
   cd minishell
   ```

2. **Compile the program**:
   ```bash
   make
   ```

3. This command generates an executable called `minishell` in the root of the project.

## Usage

Launch **Minishell** by running the executable:

```bash
./minishell
```

Once started, you can use it similarly to a standard shell. **Minishell** will interpret each line of input, execute commands, and display the output in the terminal.

Examples:

```bash
# Basic commands
minishell> ls -l
total 224
-rw-r--r--   1 asut  staff    3497 13 nov 12:39 Makefile
drwxr-xr-x   3 asut  staff      96 13 nov 12:30 inc
-rwxr-xr-x   1 asut  staff  102808 13 nov 12:40 minishell
drwxr-xr-x  12 asut  staff     384 13 nov 12:31 src
minishell> echo "Hello, Minishell!"
Hello, Minishell!

# Environment variables
minishell> export VAR="42"
minishell> echo $VAR
42

# Using pipes and redirection
minishell> cat file.txt | grep "searched_term" > result.txt
# > will create the result.txt file containing the lines containing the "searched_term"
```

## Shell Commands Supported

**Minishell** supports the following commands, either as built-ins or by executing system commands:

| Command   | Description                           |
|-----------|---------------------------------------|
| `echo`    | Print arguments to the standard output |
| `cd`      | Change the current directory          |
| `pwd`     | Print the current working directory   |
| `export`  | Set an environment variable           |
| `unset`   | Unset an environment variable         |
| `env`     | Display all environment variables     |
| `exit`    | Exit the shell                        |

Additionally, **Minishell** supports external commands found in the system's `$PATH`.

## Author

- GitHub: [@asut00](https://github.com/asut00)  
- 42 Intra: `asuteau`
