# Simple Compiler for Education

### 📌 Overview 
This repository contains my Bachelor’s Thesis (TFG) project, focused on the design and implementation of a compiler. 
The project explores the main stages of compilation, from source code processing to code generation, with an emphasis on software architecture, correctness, and system-level reasoning. 

The goal of this project was to apply theoretical computer science concepts in a practical and structured software engineering context, building a working simple compiler pipeline that students can use to understand the compilation stages. 

### 🧠 Project Objectives 
- Design and implement a complete compilation pipeline
- Apply formal language and compiler theory to real code
- Build modular and maintainable components

### ⚙️ Compiler Structure
The project is organized around the classical compiler phases: 
- Lexical Analysis 
- Tokenization of source code
- Syntax Analysis
- Parsing and grammar validation
- Semantic Analysis
- Symbol management and semantic checks
- Intermediate Representation
- Structured internal model
- Code Generation 
- Target code emission

Each phase is implemented as a clearly separated module, enabling easier reasoning, testing, and extension. 

### 🛠️ Technologies & Concepts 
- Programming Languages: C
- Bottom-up Parsing
- Concrete Syntax Trees (CST)
- Modular software architecture

### Features
- Addition and substraction (+/-)
- Multiplication (*)
- Use of parenthesis

This is an input example:
```c
2+3
```
  
### 🚀 How to Run
```bash
gcc main.c -o my_program
./my_program
```

### 📌 Future Improvements
- Optimization passes
- Extended language features
- Improved error handling
- Additional target architectures

### 👤 Author
Pau Alcaide Canet
Computer Engineering Graduate
[LinkedIn](https://www.linkedin.com/in/pau-alcaide-canet) · [GitHub](https://github.com/PauAlcaideCanet)
