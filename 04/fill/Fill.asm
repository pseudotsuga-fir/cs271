// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Andrew Hepworth
(CYCLE)
  @SCREEN	// Go to the first address of the screen
  D=A	
  @address	// Create an address label that holds our current location
  M=D
  @8192
  D=A
  @counter	// Create a counter label we can decrement and check if it reaches the end of screen
  M=D
(LOOP)
  @KBD
  D=M
  @black
  D;JGT
  @address	// Go to our current address
  D=M		// Set D to be out current address
  A=M		// Jump to the current address
  M=0		// Set the 16 pixels of this address to white
  @1
  D=D+A         // Add one to our current position
  @address
  M=D           // Update our address
  @counter
  M=M-1
  D=M
  @LOOP
  D;JGT
(black)
  @address      // Go to our current address
  D=M           // Set D to be out current address
  A=M           // Jump to the current address
  M=-1          // Set the 16 pixels of this address to black
  @1
  D=D+A		// Add one to our current position
  @address	
  M=D		// Update our address
  @counter
  M=M-1
  D=M
  @LOOP
  D;JGT
  @CYCLE
  0;JMP
(INFINITE_LOOP)
  @INFINITE_LOOP
  0;JMP

