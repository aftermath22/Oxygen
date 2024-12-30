# Oxygen Programming Language

Oxygen is a small, compiled programming language that targets x86_64 assembly. It features basic arithmetic operations, variables, control flow, and scoping rules. \
I have learned most of the things from a youtube tutorial by 'Pixeled' and this is the [link](https://www.youtube.com/watch?v=vcSijrRsrY0&list=PLUDlas_Zy_qC7c5tCgTMYq2idyyT241qs) to his playlist.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Building](#building)
- [Language Syntax](#language-syntax)
- [Implementation Details](#implementation-details)
- [Examples](#examples)

## Overview

OXY is implemented in C++ and follows a traditional compiler pipeline:
1. Lexical Analysis (Tokenization)
2. Parsing
3. Code Generation (to x86_64 assembly)

The compiler outputs assembly code which is then assembled and linked using NASM and LD respectively.

## Features

- Integer arithmetic (addition, subtraction, multiplication, division)
- Variable declarations and assignments
- Scoping rules with block-level scope
- Control flow statements (if, elif, else)
- Comments (both single-line and multi-line)
- Exit statements

## Project Structure

The project consists of several key components:

- `main.cpp`: Entry point that orchestrates the compilation process
- `tokenization.hpp`: Handles lexical analysis
- `parser.hpp`: Implements recursive descent parsing
- `generation.hpp`: Generates x86_64 assembly code
- `arena.hpp`: Implements a simple memory arena for AST node allocation

### Component Details

#### Arena Allocator
- Custom memory management system
- Provides efficient allocation for AST nodes
- Uses a simple bump allocator approach
- Supports move semantics but not copying

#### Tokenizer
- Breaks source code into tokens
- Handles keywords, identifiers, numbers, and operators
- Supports both single-line (`//`) and multi-line (`/* */`) comments
- Tracks line numbers for error reporting

#### Parser
- Implements recursive descent parsing
- Builds an Abstract Syntax Tree (AST)
- Handles operator precedence
- Provides detailed error messages
- Uses the arena allocator for memory management

#### Code Generator
- Generates x86_64 assembly code
- Implements stack-based variable storage
- Handles proper scope management
- Generates efficient arithmetic operations
- Supports control flow structures

## Building

Prerequisites:
- C++ compiler with C++20 support
- NASM assembler
- LD linker

To build a program:
```bash
# Compile the program
$ ./oxy input.oxy

# This generates:
# 1. out.asm (assembly output)
# 2. out.o (object file)
# 3. out (executable)
```

## Language Syntax

### Variables
```
let x = 42;
x = x + 1;
```

### Control Flow
```
if (condition) {
    // code
} elif (other_condition) {
    // code
} else {
    // code
}
```

### Arithmetic
```
let result = (5 + 3) * 2;
let quotient = 10 / 2;
```

### Scoping
```
{
    let x = 1;
    {
        let y = 2;
        // x and y visible here
    }
    // only x visible here
}
```

### Comments
```
// Single line comment

/* Multi-line
   comment */
```

### Exit Statement
```
exit(code);  // Exits with specified code
```

## Implementation Details

### Memory Management
The project uses a custom arena allocator for efficient AST node allocation. The arena allocator:
- Pre-allocates a large block of memory (4MB by default)
- Provides fast allocation with minimal overhead
- Does not support individual deallocation
- Frees all memory at once when destroyed

### AST Structure
The AST is built using variant types for nodes, allowing for:
- Type-safe node representation
- Easy visitor pattern implementation
- Efficient memory layout

### Code Generation
Assembly generation follows these principles:
- Stack-based variable storage
- Proper alignment handling
- Efficient register usage
- Direct syscall usage for exit operations

### Error Handling
The compiler provides:
- Line number information in error messages
- Specific error messages for missing tokens
- Clear identification of undefined variables
- Validation of redeclaration attempts

## Examples

Basic arithmetic:
```
let x = 5;
let y = 10;
let z = x + y * 2;
exit(z);
```

Control flow:
```
let x = 5;
if (x > 3) {
    exit(1);
} elif (x < 0) {
    exit(2);
} else {
    exit(3);
}
```

Nested scopes:
```
let x = 1;
{
    let y = x + 1;
    {
        let z = y + 1;
        exit(z);
    }
}
```
