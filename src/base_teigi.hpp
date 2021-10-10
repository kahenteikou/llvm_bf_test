#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include <array>
#include <fstream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <vector>
struct llvm_codels{
    llvm::BasicBlock* cblock;
    llvm::BasicBlock* bblock;
    llvm::BasicBlock* eblock;
};
void loopkun_start(llvm::Function* funcptr,llvm::Value* ptrkun,llvm_codels* current_i,int indexaniki,llvm::LLVMContext& LLModuleContext,llvm::IRBuilder<>& IRBuilder);
void loopkun_end(llvm_codels* current_i,llvm::IRBuilder<>& IRBuilder);
int check_meireikun(std::string::iterator& current,std::string& currentstr);
void LL_AddValue(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,int valuekun);
void LL_AddPtr(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,int valuekun);
void LL_PUTCHAR(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,std::unique_ptr<llvm::Module>& LLMainModule);
void LL_GETCHAR(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,std::unique_ptr<llvm::Module>& LLMainModule);
