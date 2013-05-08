//-----------------------------------------------------------------------------
// minivm.h -- The basic definitions for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include "types.h"

#ifndef MINIVM_H_
#define MINIVM_H_

//---------------------------------------------------------
// TOGGLEABLE OPTIONS AND THEIR MEANINGS:

//If defined, VM will use a static, global function pointer table.
//If not defined, function tables must be provided as part of the VM context.
//#define MVM_GLOBAL_FUNTABLE


//---------------------------------------------------------
// MACRO DEFINITIONS:


//Size of the global function pointer table
#define MVM_NUM_FUNS 256

#define MVM_NUM_REGISTERS 16 //default


//---------------------------------------------------------
// DATA STRUCTURES & TYPEDEFS:


//old: typedef int (*mvmfunptr)(const uint8, const uint8, const uint8);
typedef void (*FunPtr)(struct VMContext* ctx, const uint32);

//CHANGE THE INTERNALS OF THIS FOR YOUR OWN VM!
typedef struct Reg {
    uint32 type;
    uint32 value;
} Reg;

typedef struct VMContext {
    uint32 numRegs;
    uint32 numFuns;
    Reg* r; //ptr to register array.
    FunPtr* funtable; //ptr to a funptr table.
} VMContext;


//---------------------------------------------------------
// ESOTERIC ITEMS:


#ifdef MVM_GLOBAL_FUNTABLE
//The global function pointer table.
static mvmfunptr mvm_function_table[MVM_NUM_FUNS];
static mvmfunptr2 mvm_function_table2[MVM_NUM_FUNS];
#endif

//Byte extraction macros.
#define EXTRACT_B0(i) (i & 0xFF)
#define EXTRACT_B1(i) ((i >> 8) & 0xFF)
#define EXTRACT_B2(i) ((i >> 16) & 0xFF)
#define EXTRACT_B3(i) ((i >> 24) & 0xFF)


//---------------------------------------------------------
// FUNCTIONS:


//Selects and executes a handler function. Passes the entire bytecode instruction as the argument.
//dispatch :: VMContext -> uint32 -> Effect()
void dispatch(struct VMContext* ctx, const uint32 instr);

//Initializes a VMContext in-place.
//initVMContext :: VMContext -> uint32 -> uint32 -> [Reg] -> [FunPtr] -> Effect()
void initVMContext(struct VMContext* ctx, const uint32 numRegs, const uint32 numFuns, Reg* registers, FunPtr* funtable);

//Steps the VM forward by 1 instruction, executing it in the process.
//stepVMContext :: VMContext -> Effect()
void stepVMContext(struct VMContext* ctx);


//---------------------------------------------------------
#endif //ifndef MINIFM_H_