//-----------------------------------------------------------------------------
// example.c -- A simple VM with 4 instructions.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "minivm.h"

//---------------------------------------------------------
// EXAMPLE FUNCTIONS:

void loadNToReg(struct VMContext* ctx, const uint32 instr);
void addReg(struct VMContext* ctx, const uint32 instr);
void subReg(struct VMContext* ctx, const uint32 instr);
void printReg(struct VMContext* ctx, const uint32 instr);

void loadNToReg(struct VMContext* ctx, const uint32 instr) {
    const uint8 a = EXTRACT_B1(instr);
    const uint8 b = EXTRACT_B2(instr);
  //const uint8 c = EXTRACT_B3(instr); //Not used
    ctx->r[a].value = b;
}

void addReg(struct VMContext* ctx, const uint32 instr) {
    const uint8 a = EXTRACT_B1(instr);
    const uint8 b = EXTRACT_B2(instr);
    const uint8 c = EXTRACT_B3(instr);
    ctx->r[a].value = b + c;
}

void subReg(struct VMContext* ctx, const uint32 instr) {
    const uint8 a = EXTRACT_B1(instr);
    const uint8 b = EXTRACT_B2(instr);
    const uint8 c = EXTRACT_B3(instr);
    ctx->r[a].value = b - c;
}

void printReg(struct VMContext* ctx, const uint32 instr) {
    const uint8 a = EXTRACT_B1(instr);
  //const uint8 b = EXTRACT_B2(instr); //Not used
  //const uint8 c = EXTRACT_B3(instr); //Not used
    printf("type: %d, value: %c \n", ctx->r[a].type, ctx->r[a].value);
}

//---------------------------------------------------------
// UTILITY FUNCTIONS:

void initRegs(Reg* regs, uint32 numRegs) {
    uint32 i = 0;
    for(; i < numRegs; i++) {
        regs[i].type = 0;
        regs[i].value = 0;
    }
}

//STARTER SCRIPT:
//1. load 43 ('+') to R2
//2. print contents of R2
//3. load 1 into R1
//4. terminate
//                 |1        |2       |3       |4
//escript bc.erl "[0,2,43,0, 3,2,0,0, 0,1,1,0, 0,0,0,0]." > bytecode.txt 
int main(int argc, char** argv) {
    //Local variables:
    VMContext vm;
    Reg r[16];
    FunPtr funs[4];
    uint32 counter;

    //Bytecode-loading helper variables:
    FILE* codeFile;
    char buffer[256];


    //Load code:
    if(argc >= 1) {
        codeFile = fopen(argv[1], "rb");
    } else {
        printf("USAGE: example [FILE]\n");
        goto end; //If no bytecode provided, bail out.
    }
    if(codeFile == NULL) {
        printf("great evil has occurred!\n");
        goto end; //If a file read error happeneded, bail out.
    }
    //fread returns the number of bytes read; we don't need 
    //that info in this demo, however.
    fread((void*)&buffer, 1, 12, codeFile);
    //Close what we opened
    fclose(codeFile);
    
    //Initialize funptr table:
    funs[0] = loadNToReg;
    funs[1] = addReg;
    funs[2] = subReg;
    funs[3] = printReg;

    //Initialize registers:
    initRegs(r, 16);

    //Initialize vm context:
    initVMContext(&vm, 16, 4, r, funs);

    //Set code pointer (CP) in the first register slot:
    r[0].value = (uint32)&buffer;

    //Main loop:
    counter = 0;
    while(r[1].value < 1) {
        printf("running instr: %d -> '%d', '%d', '%d', '%d'\n", counter, 
            EXTRACT_B0(*(uint32*)r[0].value),
            EXTRACT_B1(*(uint32*)r[0].value),
            EXTRACT_B2(*(uint32*)r[0].value),
            EXTRACT_B3(*(uint32*)r[0].value));

        stepVMContext(&vm);
        counter++;
    }

end:
    return 0;
}


















