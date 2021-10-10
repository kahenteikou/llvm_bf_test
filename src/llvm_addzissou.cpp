#include "base_teigi.hpp"
void LL_AddValue(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,int valuekun){
    llvm::Value* pvll=IRBuilder.CreateLoad(datameirei_ptr_ll->getType()->getPointerElementType(),datameirei_ptr_ll);
    IRBuilder.CreateStore(
        IRBuilder.CreateAdd(
            IRBuilder.CreateLoad(pvll->getType()->getPointerElementType(),pvll),
            IRBuilder.getInt8(valuekun)
        ),pvll
    );
}