//-----------------------------------------------------------------------------
// example.c -- A simple VM with 4 instructions.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "../../minivm.h"

//---------------------------------------------------------
// EXAMPLE FUNCTIONS:

void loadNToReg(struct VMContext* ctx, const uint32_t instr);
void addReg(struct VMContext* ctx, const uint32_t instr);
void subReg(struct VMContext* ctx, const uint32_t instr);
void printReg(struct VMContext* ctx, const uint32_t instr);


void loadNToReg(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
  //const uint8_t c = EXTRACT_B3(instr); //Not used
    ctx->r[a].value = b;
}

void addReg(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value + ctx->r[c].value;
}

void subReg(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value - ctx->r[c].value;
}

void printReg(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
  //const uint8_t b = EXTRACT_B2(instr); //Not used
  //const uint8_t c = EXTRACT_B3(instr); //Not used
    printf("type: %d, value: %c \n", ctx->r[a].type, ctx->r[a].value);
}


//---------------------------------------------------------
// UTILITY FUNCTIONS:

void initRegs(Reg* regs, uint32_t numRegs) {
    uint32_t i;

    for(i = 0; i < numRegs; i++) {
        regs[i].type = 0;
        regs[i].value = 0;
    }
}


// STARTER SCRIPT:
// 1. load 43 ('+') to R2
// 2. print contents of R2
// 3. load 1 into R1
// 4. terminate
//                |1        |2       |3       |4
// python bc.py "[0,2,43,0, 3,2,0,0, 0,1,1,0, 0,0,0,0]." > bytecode.txt 
int main(int argc, char** argv) {
    // Local variables:
    VMContext vm;
    Reg       r[16];
    FunPtr    funs[4];
    uint32_t  i;
    uint32_t* pc;      // Program-Counter (PC)

    // Bytecode-loading helper variables:
    FILE* bytecodeFile;
    char  buffer[256];

    // Load code:
    if(argc >= 1) {
        bytecodeFile = fopen(argv[1], "rb");
    } else {
        printf("USAGE: example [FILE]\n");
        return 1; // If no bytecode provided, bail out.
    }

    if(bytecodeFile == NULL) {
        printf("Could not load bytecode file \'%s\'.\n", argv[1]);
        return 1; // If a file read error happeneded, bail out.
    }

    // fread returns the number of bytes read; we don't need 
    // that info in this demo, however.
    fread((void*)&buffer, 1, 12, bytecodeFile);
    // Close what we opened
    fclose(bytecodeFile);
    
    // Initialize funptr table:
    funs[0] = loadNToReg;
    funs[1] = addReg;
    funs[2] = subReg;
    funs[3] = printReg;

    // Initialize registers:
    initRegs(r, 16);

    // Initialize vm context:
    initVMContext(&vm, 16, 4, r, funs);

    // Set Program Counter (PC) to start of opcode buffer:
    pc = (uint32_t*) &buffer;

    // Main loop:
    i = 0;
    while(r[1].value < 1) {
        printf("Running instr: %d -> '%d', '%d', '%d', '%d'\n", i, 
            EXTRACT_B0(*pc),
            EXTRACT_B1(*pc),
            EXTRACT_B2(*pc),
            EXTRACT_B3(*pc));

        stepVMContext(&vm, &pc);
        i++;
    }

    // Return 0 to indicate normal termination.
    return 0;
}

