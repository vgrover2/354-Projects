.file	"To_Upper.s"
	.text
	.globl	To_Upper
	.type	To_Upper, @function

/* **
    Name: VEDANT GROVER
    Wisc ID Number: 9081621030
    Wisc Email: vgrover2@wisc.edu
** */


To_Upper:

# C version

/* **
    Write the equivalent C code to this function here (in the comment block)

    #include <stdio.h>
    void toUpper(char* c){
        if((*c < 123) && (*c > 96)){
            *c = *c - 32;
        }
        return;
    }

** */



# Memory Layout
/* ** 
    Make a table showing the stack frame for your function (in the comment block)
    The first column should have a memory address (e.g. 8(%rsp))
    The second column should be the name of the C variable used above
    Update the example below with your variables and memory addresses
        -8(%rbp)  |  char s
        
** */


# Prologue
pushq %rbp      # Setting stack frame
movq %rsp, %rbp # Setting the current address of %rsp to %rbp
subq $8, %rsp   # Reserve 8 bytes on the stack 


# This code prints the letter 'a' (ascii value 97)
# Use this for debugging
# Comment out when finished - your function should not print anything
# Note putchar overwrites all caller saved registers including argument registers
	# movl	$97, %eax
	# movl	%eax, %edi
	# call	putchar@PLT


# Body of function

    # initialize the variables
    movl $-1, -4(%rbp) 

    TOP_OF_LOOP:
    movq %rdi, %rax # moving *c to %rax from %rdi

    movb $123, %bl # ascii value of z is 122, so comparison is made to 123
    movb $96, %dl  # ascii value of a is 97, so comparison is made to 96
    
    movb (%rax), %cl
    movb $0, %r8b # checking if string is terminated

    LOOP_BODY:
    cmpb %bl, %cl # comparing the character's ascii value with 123
    jge CHAR_NEXT # the current character doesn't get modified if it's >= 123

    cmpb %dl, %cl # comparing the character's ascii value with 96
    jle CHAR_NEXT # the current character doesn't get modified if it's <= 123
    
    # at this point it's confirmed the character is a lower case as its ascii
    # value is between 97 and 122 (inclusive)

    subb $32, (%rax) # minus 32 from current value to convert it to upper case

    CHAR_NEXT:
    addq $1, %rax # increment pointer 
    movb (%rax), %cl # update the character
    cmpb %r8b, %cl # go back to the loop if the new character isn't null terminator
    jnz LOOP_BODY
    movq %rax, -8(%rbp) # store pointer back on stack

    END:


# Epilogue
    addq $8, %rsp # %rsp goes back to inital location
    popq %rbp     # %rbp gets popped from stack
    ret           # returns the function To_Upper