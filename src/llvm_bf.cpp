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
                //puts("plus_value +");
                {
                    llvm::Value* pvll=IRBuilder.CreateLoad(datameirei_ptr_ll->getType()->getPointerElementType(),datameirei_ptr_ll);
                    IRBuilder.CreateStore(
                        IRBuilder.CreateAdd(
                            IRBuilder.CreateLoad(pvll->getType()->getPointerElementType(),pvll),
                            IRBuilder.getInt8(1)
                        ),pvll
                    );
                }
                //++*datameirei_ptr;
                

                break;
            case 1:
                //puts("minus_value -");
                //--*datameirei_ptr;
                {
                    
                    llvm::Value* pvll=IRBuilder.CreateLoad(datameirei_ptr_ll->getType()->getPointerElementType(),datameirei_ptr_ll);
                    IRBuilder.CreateStore(
                        IRBuilder.CreateAdd(
                            IRBuilder.CreateLoad(pvll->getType()->getPointerElementType(),pvll),
                            IRBuilder.getInt8(-1)
                        ),pvll
                    );
                }
                break;
            case 2:
                //puts("outkun . ");
                //putchar(*datameirei_ptr);
                {
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
                break;
            case 3:
                //puts("readinputkun ,");
                //*datameirei_ptr=getchar();
                {
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
                break;
            case 4:
                //puts("jumps [");
                /*
                if(!*datameirei_ptr) {
                    
                    while(true){
                        if(code_str.size() >= jumpe.size() && 
                        std::equal(std::begin(jumpe),std::end(jumpe),current_indexkkun)){
                            break;
                        }else{
                            current_indexkkun=std::next(current_indexkkun);
                        }
                    }
                }*/
                loopkun_start(llmainfunc,datameirei_ptr_ll,codews_ptr++,whileindexkun++,LLModuleContext,IRBuilder);
                break;
            case 5:
                //puts("jumpe ]");
                /*
                if(*datameirei_ptr){    
                    while(true){
                        if(code_str.size() >= jumps.size() && 
                        std::equal(std::begin(jumps),std::end(jumps),current_indexkkun)){
                            current_indexkkun=std::next(current_indexkkun,jumps.size());
                            break;
                        }else{
                            current_indexkkun=std::prev(current_indexkkun);
                        }
                    }
                }*/
                loopkun_end(--codews_ptr,IRBuilder);
                break;
            case 6:
                //puts("ptrincr >");
                //++datameirei_ptr;

                {
                    
                    IRBuilder.CreateStore(
                        IRBuilder.CreateInBoundsGEP(
                            IRBuilder.getInt8Ty(),
                            IRBuilder.CreateLoad(datameirei_ptr_ll),
                            IRBuilder.getInt32(1)
                        ),datameirei_ptr_ll
                    );
                }
                break;
            case 7:
                //puts("ptrdecr < ");
                //--datameirei_ptr;
                {
                    
                    IRBuilder.CreateStore(
                        IRBuilder.CreateInBoundsGEP(
                            IRBuilder.getInt8Ty(),
                            IRBuilder.CreateLoad(datameirei_ptr_ll),
                            IRBuilder.getInt32(-1)
                        ),datameirei_ptr_ll
                    );
                }
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
