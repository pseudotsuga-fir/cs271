// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Andrew Hepworth
  @R2
  M=0
  @R1	//Go to first num
  D=M	//Set data to first num
  @INFINITE_LOOP
  D;JEQ
  @R0
  D=M
  @INFINITE_LOOP
  D;JEQ
(ADD_R2)
  @R0
  D=M
  @R2
  M=D+M	//Add first num to itself
  @R1
  D=M-1
  M=D
  @ADD_R2
  D;JGT
(INFINITE_LOOP)
  @INFINITE_LOOP
  0;JMP
