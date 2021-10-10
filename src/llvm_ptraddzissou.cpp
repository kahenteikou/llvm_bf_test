#include "base_teigi.hpp"
void LL_AddPtr(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,int valuekun){
    IRBuilder.CreateStore(
        IRBuilder.CreateInBoundsGEP(
            IRBuilder.getInt8Ty(),
            IRBuilder.CreateLoad(datameirei_ptr_ll),
            IRBuilder.getInt32(valuekun)
        ),datameirei_ptr_ll
    );
}