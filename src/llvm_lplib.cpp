#include "base_teigi.hpp"

void loopkun_start(llvm::Function* funcptr,llvm::Value* ptrkun,llvm_codels* current_i,int indexaniki,llvm::LLVMContext& LLModuleContext,llvm::IRBuilder<>& IRBuilder){
    current_i->cblock=llvm::BasicBlock::Create(
        LLModuleContext,std::string("w_c")+std::to_string(indexaniki),funcptr);
    current_i->bblock=llvm::BasicBlock::Create(
        LLModuleContext,std::string("w_b")+std::to_string(indexaniki),funcptr);    
    current_i->eblock=llvm::BasicBlock::Create(
        LLModuleContext,std::string("w_e")+std::to_string(indexaniki),funcptr);
    IRBuilder.CreateBr(current_i->cblock);
    IRBuilder.SetInsertPoint(current_i->cblock);
    IRBuilder.CreateCondBr(
        IRBuilder.CreateICmpNE(
            IRBuilder.CreateLoad(IRBuilder.CreateLoad(ptrkun)),
            IRBuilder.getInt8(0)
        ),
        current_i->bblock,
        current_i->eblock
    );
    IRBuilder.SetInsertPoint(current_i->bblock);
}
void loopkun_end(llvm_codels* current_i,llvm::IRBuilder<>& IRBuilder){
    IRBuilder.CreateBr(current_i->cblock);
    IRBuilder.SetInsertPoint(current_i->eblock);
}