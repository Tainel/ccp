# MAKEFILE - C COMPILED PROGRAMS

# Makefile for the CCP project.

#______________________________________________________________________________

# ------ VARIABLES ------ #

# Special variables.
.RECIPEPREFIX := >

# Compiler.
CC := gcc
CFLAGS := -std=c17 -Wpedantic -Wall -Wextra -Wconversion -Wshadow -Werror\
-Ofast -funroll-loops -s

# Archiver.
AR := ar
AROPS := rcs

# Executable targets.
IND := indent
SEC := secure

# Subdirectories.
BIN := bin/
HDR := include/
LIB := lib/
LCL := local/
OBJ := obj/
SRC := source/
MNS := $(SRC)main/
UTL := $(SRC)utility/

# Main files.
MAIN1 := $(MNS)$(IND).c
MAIN2 := $(MNS)$(SEC).c

# Exclusive header files.
BSC := $(HDR)basics.h

# Libraries.
LIB1 := $(LIB)lib$(IND).a
LIB2 := $(LIB)lib$(SEC).a
LIBS := $(LIB1) $(LIB2)

# Utility file names.
F01 := random
F02 := aesctr
F03 := primes
F04 := vector
F05 := slnode
F06 := stack
F07 := queue
F08 := dlnode
F09 := deque
F10 := list
F11 := heap
F12 := bsnode
F13 := bst
F14 := map
F15 := strings
F16 := text
FLS := $(F01) $(F02) $(F03) $(F04) $(F05) $(F06) $(F07) $(F08) $(F09) $(F10)\
$(F11) $(F12) $(F13) $(F14) $(F15) $(F16)

# Utility header files.
H01 := $(HDR)$(F01).h
H02 := $(HDR)$(F02).h
H03 := $(HDR)$(F03).h
H04 := $(HDR)$(F04).h
H05 := $(HDR)$(F05).h
H06 := $(HDR)$(F06).h
H07 := $(HDR)$(F07).h
H08 := $(HDR)$(F08).h
H09 := $(HDR)$(F09).h
H10 := $(HDR)$(F10).h
H11 := $(HDR)$(F11).h
H12 := $(HDR)$(F12).h
H13 := $(HDR)$(F13).h
H14 := $(HDR)$(F14).h
H15 := $(HDR)$(F15).h
H16 := $(HDR)$(F16).h

# Utility source files.
S01 := $(UTL)$(F01).c
S02 := $(UTL)$(F02).c
S03 := $(UTL)$(F03).c
S04 := $(UTL)$(F04).c
S05 := $(UTL)$(F05).c
S06 := $(UTL)$(F06).c
S07 := $(UTL)$(F07).c
S08 := $(UTL)$(F08).c
S09 := $(UTL)$(F09).c
S10 := $(UTL)$(F10).c
S11 := $(UTL)$(F11).c
S12 := $(UTL)$(F12).c
S13 := $(UTL)$(F13).c
S14 := $(UTL)$(F14).c
S15 := $(UTL)$(F15).c
S16 := $(UTL)$(F16).c

# Object files.
O01 := $(OBJ)$(F01).o
O02 := $(OBJ)$(F02).o
O03 := $(OBJ)$(F03).o
O04 := $(OBJ)$(F04).o
O05 := $(OBJ)$(F05).o
O06 := $(OBJ)$(F06).o
O07 := $(OBJ)$(F07).o
O08 := $(OBJ)$(F08).o
O09 := $(OBJ)$(F09).o
O10 := $(OBJ)$(F10).o
O11 := $(OBJ)$(F11).o
O12 := $(OBJ)$(F12).o
O13 := $(OBJ)$(F13).o
O14 := $(OBJ)$(F14).o
O15 := $(OBJ)$(F15).o
O16 := $(OBJ)$(F16).o
OBJS := $(patsubst %,$(OBJ)%.o,$(FLS))

# OS-dependant variables.
ifeq ($(OS),Windows_NT)
  OSFILE := $(LCL:/=\)os
  BLT := _BUILT_IN_WINDOWS_
  RM := del /f /q
  TEMP := $(BIN:/=\)* $(LIB:/=\)* $(OBJ:/=\)*
  BIN1 := $(BIN)$(IND).exe
  BIN2 := $(BIN)$(SEC).exe
else ifndef OS
  UNAME := $(shell uname -s)
  ifeq ($(UNAME),Linux)
    OSFILE := $(LCL)os
    BLT := _BUILT_IN_GNU/LINUX_
    RM := rm -f
    TEMP := $(BIN)* $(LIB)* $(OBJ)*
    BIN1 := $(BIN)$(IND)
    BIN2 := $(BIN)$(SEC)
  endif
endif

# Executables.
BINS := $(BIN1) $(BIN2)

# Last project state.
ifdef OSFILE
  OSLAST := $(file < $(OSFILE))
endif

#______________________________________________________________________________

# ------ ALL ------ #

# Default target.
.PHONY: all
all: build

#______________________________________________________________________________

# ------ TARGETS ------ #

# Build the project.
.PHONY: build
build: initbuild $(OBJS) $(LIBS) $(BINS)

# Execute indent.
.PHONY: $(IND)
$(IND): initbuild $(BIN1)
>$(BIN1) $(ARGS)

# Execute secure.
.PHONY: $(SEC)
$(SEC): initbuild $(BIN2)
>$(BIN2) $(ARGS)

# Delete all executables, libraries and object files.
.PHONY: clean
clean: initclean

#______________________________________________________________________________

# ------ AUXILIARIES ------ #

# Initialize the project state to a built state if possible.
.PHONY: initbuild
initbuild:
ifndef OSFILE
>$(error Cannot build due to unknown OS)
else ifneq ($(OSLAST),$(BLT))
  ifdef OSLAST
>$(RM) $(TEMP)
  endif
>$(file > $(OSFILE),$(BLT))
endif

# Build object files.
# - Random:
$(O01): $(S01) $(H01)
>$(CC) $(CFLAGS) -c $< -o $@
# - Encryption:
$(O02): $(S02) $(H02)
>$(CC) $(CFLAGS) -c $< -o $@
# - Primes:
$(O03): $(S03) $(H03)
>$(CC) $(CFLAGS) -c $< -o $@
# - Vector:
$(O04): $(S04) $(H04) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Singly Linked Node:
$(O05): $(S05) $(H05) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Stack:
$(O06): $(S06) $(H06) $(H05) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Queue:
$(O07): $(S07) $(H07) $(H05) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Doubly Linked Node:
$(O08): $(S08) $(H08) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Deque:
$(O09): $(S09) $(H09) $(H08) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Linked List:
$(O10): $(S10) $(H10) $(H08) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Heap:
$(O11): $(S11) $(H11) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Binary Search Node:
$(O12): $(S12) $(H12) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Binary Search Tree:
$(O13): $(S13) $(H13) $(H12) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Hash Table:
$(O14): $(S14) $(H14) $(H03) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Strings:
$(O15): $(S15) $(H15) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@
# - Text:
$(O16): $(S16) $(H16) $(H15) $(H10) $(H08) $(BSC)
>$(CC) $(CFLAGS) -c $< -o $@

# Build libraries.
# - Indent library:
$(LIB1): $(O16) $(O15) $(O13) $(O12) $(O10) $(O08)
>$(AR) $(AROPS) $@ $^
# - Secure library:
$(LIB2): $(O15) $(O02)
>$(AR) $(AROPS) $@ $^

# Build executables.
# - Indent executable:
$(BIN1): $(MAIN1) $(LIB1)
>$(CC) $(CFLAGS) $^ -o $@
# - Secure executable:
$(BIN2): $(MAIN2) $(LIB2)
>$(CC) $(CFLAGS) $^ -o $@

# Initialize the project state to a clean state if possible.
.PHONY: initclean
initclean:
ifndef OSFILE
>$(error Cannot clean due to unknown OS)
else ifdef OSLAST
>$(RM) $(TEMP) $(OSFILE)
endif

#______________________________________________________________________________
