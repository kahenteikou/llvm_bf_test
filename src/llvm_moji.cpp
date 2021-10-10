#include "base_teigi.hpp"
void LL_PUTCHAR(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,std::unique_ptr<llvm::Module>& LLMainModule){
    llvm::Function* putchar_ll=llvm::cast<llvm::Function>
    (
        LLMainModule->getOrInsertFunction(
            "putchar",
            IRBuilder.getInt32Ty(),
            IRBuilder.getInt32Ty()
        ).getCallee()
    );
    IRBuilder.CreateCall(
        putchar_ll,
        IRBuilder.CreateSExt(
            IRBuilder.CreateLoad(IRBuilder.CreateLoad(datameirei_ptr_ll)),
            IRBuilder.getInt32Ty()
        )
    );
}

void LL_GETCHAR(llvm::IRBuilder<>& IRBuilder,llvm::Value*& datameirei_ptr_ll,std::unique_ptr<llvm::Module>& LLMainModule){
    llvm::Function* getchar_ll=llvm::cast<llvm::Function>
    (
        LLMainModule->getOrInsertFunction(
            "getchar",
            IRBuilder.getInt32Ty()
        ).getCallee()
    );
    llvm::Value* i32kun_char=IRBuilder.CreateCall(
        getchar_ll
    );
    llvm::Value* current_ptr=IRBuilder.CreateLoad(datameirei_ptr_ll);
    IRBuilder.CreateStore(
        IRBuilder.CreateTrunc(
            i32kun_char,
            IRBuilder.getInt8Ty()
        ),
        current_ptr
    );
}