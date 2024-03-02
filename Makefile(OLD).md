# Project Compilation Guide

This README outlines the process for using the provided Makefile to automate the compilation of an autograder program and multiple instances of a template program. The Makefile enables the efficient creation of a specified number of template program binaries.

## Prerequisites

Before proceeding, ensure the following tools are installed and accessible from your command line or terminal:

- **GNU Make**
- **GCC (GNU Compiler Collection)**

## File Structure

- **`autograder.c`**: Source code for the autograder program.
- **`template.c`**: Source code for the template program. This will be compiled into multiple binaries.

## Makefile Overview

### Variables

- **`CC`**: Specifies the compiler, defaulting to `gcc`.
- **`CFLAGS`**: Compiler flags for the compilation process. Defaults to `-Wall` (for all warnings) and `-g` (for debugging information).
- **`N`**: The number of template program binaries to compile. This can be set when invoking `make`.
- **`SOURCE_FILE`**: The source file for the template program, defaulting to `template.c`.
- **`TEST_DIR`**: The directory where compiled template binaries will be placed, defaulting to `./test`.

### Targets

- **`all`**: The default target that compiles both the autograder and the specified number of template binaries.
- **`autograder`**: Compiles the autograder program.
- **`clean`**: Removes all compiled binaries and the autograder executable.

## Usage

### Compile Everything

To compile both the autograder and the default number of template binaries:

To compile both the autograder and the default number of template binaries:

```bash
make
```

Or explicitly:

```bash
make all
```

### Specify Number of Binaries

To compile a specific number of template binaries, set `N`:

```bash
make N=5
```

This compiles the autograder and five instances of the template program.

### Compile Only the Autograder

To compile only the autograder program:

```bash
make autograder
```

### Clean Compiled Files

To remove default number of template binaries:

```bash
make clean
```

To remove a specific number of template binaries, set `N`:
```bash
make clean N=5
```


