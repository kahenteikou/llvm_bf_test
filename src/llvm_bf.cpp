#include "base_teigi.hpp"
int main(int argc,char* argv[]){
    llvm::LLVMContext LLModuleContext;
    llvm::IRBuilder<> IRBuilder(LLModuleContext);
    std::unique_ptr<llvm::Module> LLMainModule;
    std::ifstream inputstream(argv[1]);
    std::string code_str;
    std::string::iterator current_indexkkun;
    if(inputstream.fail()){
        std::cerr << "ERR File Load" << std::endl;
        return -1;
    }
    int resultkun=0;
    LLMainModule=std::make_unique<llvm::Module>("main",LLModuleContext); // create module (source file)
    llvm::Function *llmainfunc=llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt32Ty(LLModuleContext),false),
        llvm::Function::ExternalLinkage,"main",LLMainModule.get()); // create main method
    IRBuilder.SetInsertPoint(llvm::BasicBlock::Create(LLModuleContext,"",llmainfunc)); // set target method
    llvm::Value* datakun_ll;
    llvm::Value* datameirei_ptr_ll;
    datakun_ll=IRBuilder.CreateAlloca(IRBuilder.getInt8PtrTy(),nullptr,"datakun");
    datameirei_ptr_ll=IRBuilder.CreateAlloca(IRBuilder.getInt8PtrTy(),nullptr,"datameirei_ptr");
    {
        llvm::Function* callocfunc=llvm::cast<llvm::Function>(
            LLMainModule->getOrInsertFunction("calloc",
            IRBuilder.getInt8PtrTy(),
            IRBuilder.getInt64Ty(),
            IRBuilder.getInt64Ty()
            ).getCallee()
        );
        llvm::Value*  dtptrvalue=   IRBuilder.CreateCall(callocfunc,
        {
            IRBuilder.getInt64(1000000),IRBuilder.getInt64(1)
        });
        IRBuilder.CreateStore(dtptrvalue,datakun_ll);
        IRBuilder.CreateStore(dtptrvalue,datameirei_ptr_ll);
    }
    std::string bufstr;
    while(getline(inputstream,bufstr)){
        code_str=code_str+bufstr;
    }
    current_indexkkun=code_str.begin();
    llvm_codels code_ws[100000];
    llvm_codels* codews_ptr=code_ws;
    int whileindexkun=0;
    while(current_indexkkun != code_str.end()){
        resultkun=check_meireikun(current_indexkkun,code_str);
        switch(resultkun){
            case 0:
                LL_AddValue(IRBuilder,datameirei_ptr_ll,1);
                break;
            case 1:
                LL_AddValue(IRBuilder,datameirei_ptr_ll,-1);
                break;
            case 2:
                LL_PUTCHAR(IRBuilder,datameirei_ptr_ll,LLMainModule);
                break;
            case 3:
                LL_GETCHAR(IRBuilder,datameirei_ptr_ll,LLMainModule);
                break;
            case 4:
                loopkun_start(llmainfunc,datameirei_ptr_ll,codews_ptr++,whileindexkun++,LLModuleContext,IRBuilder);
                break;
            case 5:
                loopkun_end(--codews_ptr,IRBuilder);
                break;
            case 6:
                LL_AddPtr(IRBuilder,datameirei_ptr_ll,1);
                break;
            case 7:
                LL_AddPtr(IRBuilder,datameirei_ptr_ll,-1);
                break;
            case 255:
                std::cerr << "syntax error" << std::endl;
                return -114;
        }
    }
    {
        llvm::Function* freefunc=llvm::cast<llvm::Function>(
            LLMainModule->getOrInsertFunction(
                "free",
                IRBuilder.getVoidTy(),
                IRBuilder.getInt8PtrTy()
            ).getCallee()
        );
        IRBuilder.CreateCall(freefunc,{
               IRBuilder.CreateLoad(datakun_ll)
        });
    }
    IRBuilder.CreateRet(IRBuilder.getInt32(0));
    std::error_code errcodekun;
    llvm::raw_fd_ostream outstream(argv[2],errcodekun,llvm::sys::fs::OpenFlags::OF_None);
    llvm::WriteBitcodeToFile(*LLMainModule.get(),outstream);
    //LLMainModule->print(llvm::errs(),nullptr);

    return 0;
}
