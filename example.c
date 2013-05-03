//-----------------------------------------------------------------------------
// example.c -- An example VM with a stack and block-allocated heap.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- New BSD License
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
    const uint8 c = EXTRACT_B3(instr);
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
    const uint8 b = EXTRACT_B2(instr);
    const uint8 c = EXTRACT_B3(instr);
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
//Loads the value 5 into r3, prints it out on the command line, and then exits by setting r2 to 1.
//                 |load '+' into r[2].      |print contents of r[2]. |set r[1].value to 1     |pad.
//$ python bc.py '[(1,0),(1,2),(1,43),(1,0), (1,3),(1,2),(1,0),(1,0), (1,0),(1,1),(1,1),(1,0), (4,0)]' > bytecode.txt
int main(int argc, char** argv) {
    //local variables:
    VMContext vm;
    Reg r[16];
    FunPtr funs[4];
    uint32 counter;

    //bytecode-loading helper variables:
    FILE* codeFile;
    uint32 bytesRead;
    char buffer[256];


    //load code:
    codeFile = fopen("bytecode", "rb");
    if(codeFile == NULL) {
        printf("great evil has occurred!\n");
    }
    bytesRead = fread((void*)&buffer, 1, 12, codeFile); //can use 'bytesRead' to check bytecode size.
    fclose(codeFile);
    
    //initialize funptr table:
    funs[0] = loadNToReg;
    funs[1] = addReg;
    funs[2] = subReg;
    funs[3] = printReg;

    //initialize registers:
    initRegs(r, 16);

    //initialize vm context:
    initVMContext(&vm, 16, 4, r, funs);

    //set code pointer in the first register slot:
    r[0].value = (uint32)&buffer;

    //main loop:
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

    return 0;
}


















