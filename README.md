# **C Compiled Programs**

The project consists of various data structures and utility functions in **C**,
as well as programs that make use of them.

The root directory **ccp/** is composed of the following:

 * **bin/**: contains the executables.
 * **include/**: contains the headers.
 * **lib/**: contains the libraries.
 * **local/**: contains project data.
 * **obj/**: contains the object files.
 * **source/**: contains the source code.
 * **Makefile**: set of instructions to use the project.
 * **README.md**: general information about the project.

The project is intended for **Windows** and **GNU/Linux**. Besides, the
building tool **make** is required. The available targets for it are:

 * **build**: build the project, default target.
 * **indent**: execute an indentation program.
 * **secure**: execute an encryption program.
 * **clean**: delete all executables, libraries and object files.

For executable targets, command line arguments can be passed using the **ARGS**
variable. If one such target is executed, only the necessary files are built
for it to execute.

When switching from one OS to another, all executables, libraries and object
files are built from scratch without having to clean the project manually.
