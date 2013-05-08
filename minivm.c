//-----------------------------------------------------------------------------
// minivm.c -- The basic definitions for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include "types.h"
#include "minivm.h"

//---------------------------------------------------------
// FUNCTION IMPLEMENTATIONS:


//Defers decoding of register args to the called function.
//dispatch :: VMContext -> uint32 -> Effect()
void dispatch(struct VMContext* ctx, const uint32 instr) {
    const uint8 i = EXTRACT_B0(instr);
    (*ctx->funtable[i])(ctx, instr);
}

//Initializes a VMContext in-place.
//initVMContext :: VMContext -> uint32 -> uint32 -> [Reg] -> [FunPtr] -> Effect()
void initVMContext(struct VMContext* ctx, const uint32 numRegs, const uint32 numFuns, Reg* registers, FunPtr* funtable) {
    ctx->numRegs    = numRegs;
    ctx->numFuns    = numFuns;
    ctx->r          = registers;
    ctx->funtable   = funtable;
}

//Steps the VM forward by 1 instruction, executing it in the process.
//NOTE: This function assumes that the instruction pointer is in register 0, 
//      and that there is another instruction to execute.
//stepVMContext :: VMContext -> Effect()
void stepVMContext(struct VMContext* ctx) {
    //set up for some pointer arithmetic.
    uint32* ptr = &*(uint32*)ctx->r[0].value;
    //indirection on the pointer in r0.
    uint32 instr = *(uint32*)ctx->r[0].value;
    dispatch(ctx, instr);
    //now the pointer arithmetic...
    ptr++;
    ctx->r[0].value = (uint32) ptr;
}


//---------------------------------------------------------
// OLD DISPATCH CODE POSSIBILITIES:


/*void dispatch(const uint32 instr) {
    const uint8 i = EXTRACT_B0(instr);
    const uint8 r1 = EXTRACT_B1(instr);
    const uint8 r2 = EXTRACT_B2(instr);
    const uint8 r3 = EXTRACT_B3(instr);
    (*mvm_function_table[i])(r1, r2, r3);
}*/

/*void dispatchByCases_constBytes(const uint32 instr) {
    const uint8 i = EXTRACT_B0(instr);
    const uint8 r1 = EXTRACT_B1(instr);
    const uint8 r2 = EXTRACT_B2(instr);
    const uint8 r3 = EXTRACT_B3(instr);
    switch(i) {
    case 0:
        //
    case 1:
        //
    case 2:
        //
    case 3:
        //
    default:
        ;//
    }
    return;
}*/

//---------------------------------------------------------






