MiniShell
Welcome to MiniShell, our lightweight version of a Unix shell. This project is a collaboration between Your Name and Poddani, designed to emulate basic functionalities of traditional shells like Bash.

Overview
MiniShell aims to provide a simplified environment for executing commands, managing environment variables, and handling input/output redirections. It's built to offer insight into how shells operate behind the scenes, with a focus on process management and user interaction.

Features
Execution of basic system commands.
Support for builtin commands: cd, echo, pwd, export, unset, env, and exit.
Environment variable management.
Basic signal handling (e.g., SIGINT, SIGQUIT).
Simple pipelines and redirections.
Getting Started
To use MiniShell, you'll need a Unix-like system with GCC and Make installed.

Installation:

Clone this repository:
bash
Copy code
git clone https://github.com/YourUsername/MiniShell.git
Navigate to the MiniShell directory and compile:
bash
Copy code
cd MiniShell
make
Run MiniShell:
bash
Copy code
./minishell
