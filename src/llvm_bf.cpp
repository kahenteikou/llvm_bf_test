#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include <array>
    std::string plus_value="+";
    std::string minus_value="-";
    std::string outkun=".";
    std::string readinputkun=",";
    std::string jumps="[";
    std::string jumpe="]";
    std::string ptrincr=">";
    std::string ptrdecr="<";
#include <fstream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
static llvm::LLVMContext LLModuleContext;
static llvm::IRBuilder<> IRBuilder(LLModuleContext);
static std::unique_ptr<llvm::Module> LLMainModule;
int check_meireikun(std::string::iterator& current,std::string& currentstr){
    if(currentstr.size() >= plus_value.size() && 
        std::equal(std::begin(plus_value),std::end(plus_value),current)){
            current=std::next(current,plus_value.size());
            return 0;
        }
    
    if(currentstr.size() >= minus_value.size() && 
        std::equal(std::begin(minus_value),std::end(minus_value),current)){
            current=std::next(current,minus_value.size());
            return 1;
        }
    if(currentstr.size() >= outkun.size() && 
        std::equal(std::begin(outkun),std::end(outkun),current)){
            current=std::next(current,outkun.size());
            return 2;
        }
    if(currentstr.size() >= readinputkun.size() && 
        std::equal(std::begin(readinputkun),std::end(readinputkun),current)){
            current=std::next(current,readinputkun.size());
            return 3;
        }
    if(currentstr.size() >= jumps.size() && 
        std::equal(std::begin(jumps),std::end(jumps),current)){
            current=std::next(current,jumps.size());
            return 4;
        }
    if(currentstr.size() >= jumpe.size() && 
        std::equal(std::begin(jumpe),std::end(jumpe),current)){
            current=std::next(current,jumpe.size());
            return 5;
        }
    if(currentstr.size() >= ptrincr.size() && 
        std::equal(std::begin(ptrincr),std::end(ptrincr),current)){
            current=std::next(current,ptrincr.size());
            return 6;
        }
    if(currentstr.size() >= ptrdecr.size() && 
        std::equal(std::begin(ptrdecr),std::end(ptrdecr),current)){
            current=std::next(current,ptrdecr.size());
            return 7;
        }
    return 255;
}

int main(int argc,char* argv[]){
    std::ifstream inputstream(argv[1]);
    std::string code_str;
    std::string::iterator current_indexkkun;
    if(inputstream.fail()){
        std::cerr << "ERR File Load" << std::endl;
        return -1;
    }
    int resultkun=0;
    int datakun[1000000]={0};
    int* datameirei_ptr=nullptr;
    datameirei_ptr=datakun;
    LLMainModule=std::make_unique<llvm::Module>("main",LLModuleContext); // create module (source file)
    llvm::Function *llmainfunc=llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getInt32Ty(LLModuleContext),false),
        llvm::Function::ExternalLinkage,"main",LLMainModule.get()); // create main method
    IRBuilder.SetInsertPoint(llvm::BasicBlock::Create(LLModuleContext,"",llmainfunc)); // set target method
    llvm::Value* datakun_ll=IRBuilder.CreateAlloca(IRBuilder.getInt8PtrTy(),nullptr,"datakun");
    llvm::Value* datameirei_ptr_ll=IRBuilder.CreateAlloca(IRBuilder.getInt8PtrTy(),nullptr,"datameirei_ptr");
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
    while(current_indexkkun != code_str.end()){
        resultkun=check_meireikun(current_indexkkun,code_str);
        switch(resultkun){
            case 0:
                //puts("plus_value +");
                {
                    llvm::Value* pvll=IRBuilder.CreateLoad(datameirei_ptr_ll);
                    IRBuilder.CreateStore(
                        IRBuilder.CreateAdd(
                            IRBuilder.CreateLoad(pvll),
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
                    
                    llvm::Value* pvll=IRBuilder.CreateLoad(datameirei_ptr_ll);
                    IRBuilder.CreateStore(
                        IRBuilder.CreateAdd(
                            IRBuilder.CreateLoad(pvll),
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
                if(!*datameirei_ptr) {
                    
                    while(true){
                        if(code_str.size() >= jumpe.size() && 
                        std::equal(std::begin(jumpe),std::end(jumpe),current_indexkkun)){
                            break;
                        }else{
                            current_indexkkun=std::next(current_indexkkun);
                        }
                    }
                }
                break;
            case 5:
                //puts("jumpe ]");
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
                }
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
   LLMainModule->print(llvm::errs(),nullptr);
    
    return 0;
}