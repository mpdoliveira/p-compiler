🌐 **English** | [Português](README.pt-BR.md)

# Compiler Front-End — P Language

Compiler course project developed in **C**, focused on the **front-end** of a small custom programming language (P) defined by Professor Guilherme Silva at the Federal University of São João del-Rei (UFSJ).

## What Has Been Implemented

- **Lexical analyzer:** reads a source code file character by character and converts its contents into tokens.
- **Token recognition:** identifies reserved keywords, identifiers, integer and floating-point literals, characters, strings, operators, and delimiters.
- **Error detection:** classifies invalid or unrecognized sequences as `TOKEN_ERROR`.
- **Token output:** displays each token's type, lexeme, and line number.

## How to Run

Compile and run from the repository root using GCC:

```bash
gcc compiler.c -o compiler
./compiler test.txt
```
