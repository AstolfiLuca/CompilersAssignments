# CompilersAssignments
This repository contains the code and the documentation related to the course compilers part II assignments (little "at home" projects).

Members in alphabetical order:
- Alioto Cristian Piero
- Aresta Simone
- Astolfi Luca

## Contents of this page
- [Introduction](#introduction)
- [Setup](#setup)
- [Usage](#usage)
- [Assignments](#assignments)
- [Links](#links)
- [Structure](#structure)


## Introduction
The objective of the course is to understand the theory behind the front-end of modern compilers, focusing on the compiler LLVM.

## Setup
To setup the workspace use:
```bash
make configure_env
```

To build the assignment:
```bash
make cmake assignment=<number>
```

## Usage
To run a test use:
- From .cpp to .optimized.ll 

    ```bash
    make clang assignment=<number> flag=<LLVM_flag_number> test=<testName> 
    ```

    Note:

    This make command uses `mem2reg` pass (it removes stores and loads).

- From .ll to .optimized.ll
    ```bash
    make optimize assignment=<number> p=<passName> test=<testName> 
    ```

To remove all build directories:
```bash
make clean_builds
```

## Assignments
- 1° Assignment: 
    Implementation in LLVM of:
    - Algebraic Identity
    - Strength reduction
    - Multi-Instruction Optimization

## Links
LLVM front page: https://llvm.org/

LLVM Instruction documentation: https://llvm.org/doxygen/classllvm_1_1Instruction.html

## Structure
<!-- FILETREE START -->
```
.
├── assignment1
│   ├── build
│   │   ├── CMakeCache.txt
│   │   ├── CMakeFiles
│   │   │   └── ...
│   │   ├── cmake_install.cmake
│   │   ├── libLocalOpt.so
│   │   └── Makefile
│   ├── CMakeLists.txt
│   ├── opts
│   │   ├── AlgebraicIdentity.cpp
│   │   ├── LocalOpts.cpp
│   │   ├── LocalOpts.h
│   │   ├── MultiInstruction.cpp
│   │   └── StrengthReduction.cpp
│   └── test
│       ├── bc
│       │   └── ...
│       ├── cpp
│       │   ├── algebraic_identity.cpp
│       │   ├── multi_instruction.cpp
│       │   └── strength_reduction.cpp
│       ├── ll
│       │   └── ...
│       └── ll_optimized
│           └── ...
├── makefile
└── README.md

4 directories, 7 files
```
<!-- FILETREE END -->
