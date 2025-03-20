# CompilersAssignments
This repository contains the code and the documentation related to the compilers part II assignments

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
The objective of the course is understanding the front-end of the compiler, focusing on the compiler LLVM.

## Setup
To setup the workspace use:
```bash
make configure_env
```

## Usage
To run a test use:
```bash
make runtest assignment=assignment<number> opt=opt<number> test=<name_test>
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
LLVM front page:

LLVM Instruction documentation:

https://llvm.org/doxygen/classllvm_1_1Instruction.html

## Structure
<!-- FILETREE START -->
```
.
├── academic_resources
│   ├── 1- Introduction to Evolutionary Computing.pdf
│   ├── 2 - MOO_theory_and_practice_II.pdf
│   ├── 3 - MJ_in_a_nut.pdf
│   ├── old_papers
│   ├── resources.txt
│   └── unimore_related 
├── .gitignore
├── README.md
└── requirements.txt

4 directories, 7 files
```
<!-- FILETREE END -->
