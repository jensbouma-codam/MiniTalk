# MiniTalk

MiniTalk is designed to help students understand the basics of inter-process communication (IPC) using signals. IPC is an essential concept in software development, especially when dealing with process coordination, synchronization, and signaling. The subject provides hands-on experience in building a simple messaging system using signals.

## Executable Files

- Name your executable files as `client` and `server`.

## Makefile

- You must include a Makefile that compiles your source files without relinking.

## Dependencies

- You are allowed to use your `libft` library.

## Error Handling

- Thoroughly handle errors to ensure that your program does not quit unexpectedly (e.g., segmentation fault, bus error, double free).

## Memory Management

- Ensure that your program does not have memory leaks.

## Global Variables

- You are allowed to have one global variable per program (one for the client and one for the server).
- Justify the use of global variables if you choose to implement them.

## Permitted Functions

- To complete the mandatory part of the project, you can use the following functions:
  - `write`
  - `ft_printf` (or any equivalent function you have coded)
  - `signal`
  - `sigemptyset`
  - `sigaddset`
  - `sigaction`
  - `kill`
  - `getpid`
  - `malloc`
  - `free`
  - `pause`
  - `sleep`
  - `usleep`
  - `exit`

## Mandatory Part

- Create a communication program consisting of a client and a server.
- Start the server first, and print its PID after launch.
- The client should take two parameters:
  - The server PID.
  - The string to send.
- The client must send the string passed as a parameter to the server.
- Once the server receives the string, it must print it.
- The server should display the string quickly. If it takes too long, it is considered too long.
  - Displaying 100 characters should take less than 1 second.
- The server should be able to receive strings from multiple clients in a row without needing to restart.
- Communication between the client and server must be done only using UNIX signals.
- Use only the following signals: `SIGUSR1` and `SIGUSR2`.

## Bonus Part

- The server should acknowledge every message received by sending back a signal to the client.
- Unicode characters support is a bonus feature.

**Note:** Remember to thoroughly test your program and ensure its reliability and correctness. Good luck!
