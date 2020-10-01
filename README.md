# os1
Reads from a csv file using basic Linux system calls (open, close, read, and write). Operates on this date, saves the results to a file, and also writes the content saved to the file to stdout. fork() and waitpid() system calls are used so that half the file is handled by a child process, and half by the parent.
