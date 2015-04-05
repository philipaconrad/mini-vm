//-----------------------------------------------------------------------------
// arith.c -- Arithmetic expression evaluator example.
// Copyright (c) Philip Conrad 2015-04-04 @9:11 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../minivm.h"


#define BUFF_SIZE 1024
char buffer[BUFF_SIZE];
bool is_running;


//---------------------------------------------------------
// ARITHMETIC FUNCTIONS:

void add(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value + ctx->r[c].value;
}

void sub(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value - ctx->r[c].value;
}

void multiply(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value * ctx->r[c].value;
}

void divide(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value / ctx->r[c].value;
}

void mod(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    const uint8_t c = EXTRACT_B3(instr);
    ctx->r[a].value = ctx->r[b].value % ctx->r[c].value;
}


//---------------------------------------------------------
// UTILITY FUNCTIONS:

void load_immediate(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    const uint8_t b = EXTRACT_B2(instr);
    ctx->r[a].value = b;
}

void print(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t a = EXTRACT_B1(instr);
    printf(">> %d \n", ctx->r[a].value);
}

void halt(struct VMContext* ctx, const uint32_t instr) {
    is_running = false;
}

void initRegs(Reg* regs, uint32_t numRegs) {
    uint32_t i;

    for(i = 0; i < numRegs; i++) {
        regs[i].type = 0;                                                       
        regs[i].value = 0;
    }
}



int main(int argc, char** argv) {
    VMContext vm;
    Reg       r[16];
    FunPtr    f[64];
    FILE*     bytecode;
    char      buffer[1024];
    uint32_t* pc;
    int       bytes_loaded;
    int       i;

    // Load bytecode:
    if(argc >= 1) {
        bytecode = fopen(argv[1], "rb");
    } else {
        printf("USAGE: arith [FILE]\n");
        return 1; // If no bytecode provided, bail out.
    }

    if(bytecode == NULL) {
        printf("Could not load bytecode file \'%s\'.\n", argv[1]);
        return 1; // If a file read error happeneded, bail out.
    }

    // fread returns the number of bytes read.
    bytes_loaded = fread((void*)&buffer, 1, 1024, bytecode);

    // Close the file from earlier.
    fclose(bytecode);

    printf("Loaded %d bytes (%d instructions) from %s.\n",
           bytes_loaded, (bytes_loaded/4), argv[1]);


    // Initialize the function pointer table.
    f[43] = add;            // '+' in the bytecode.
    f[45] = sub;            // '-' in the bytecode.
    f[42] = multiply;       // '*' in the bytecode.
    f[47] = divide;         // '/' in the bytecode.
    f[37] = mod;            // '%' in the bytecode.
    f[36] = load_immediate; // '$' in the bytecode.
    f[63] = print;          // '?' in the bytecode.
    f[35] = halt;           // '#' in the bytecode.

    // Initialize registers.
    initRegs(r, 16);

    // Initialize vm context.
    initVMContext(&vm, 16, 64, r, f);

    // Set Program Counter (PC) to start of opcode buffer.
    pc = (uint32_t*) &buffer;

    // Main loop.
    i = 0;
    is_running = true;

    while(is_running) {
#ifdef DEBUG
        printf("Running instr: %d -> [ '%c', '%d', '%d', '%d' ]\n", i, 
            EXTRACT_B0(*pc),
            EXTRACT_B1(*pc),
            EXTRACT_B2(*pc),
            EXTRACT_B3(*pc));
#endif
        stepVMContext(&vm, &pc);
        i++;
    }

    // Return 0 to indicate normal termination.
    return 0;
}
