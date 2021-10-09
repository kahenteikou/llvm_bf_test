#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include <array>
std::array<std::uint8_t, 1000000> data;
    std::string plus_value="plus";
    std::string minus_value="-";
    std::string outkun=".";
    std::string readinputkun=",";
    std::string jumps="[";
    std::string jumpe="]";
    std::string ptrincr=">";
    std::string ptrdecr="<";
#include <fstream>
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
    while(getline(inputstream,code_str)){
        current_indexkkun=code_str.begin();
        while(current_indexkkun != code_str.end()){
            resultkun=check_meireikun(current_indexkkun,code_str);
            switch(resultkun){
                case 0:
                    puts("plus_value +");
                    break;
                case 1:
                    puts("minus_value -");
                    break;
                case 2:
                    puts("outkun . ");
                    break;
                case 3:
                    puts("readinputkun ,");
                    break;
                case 4:
                    puts("jumps [");
                    break;
                case 5:
                    puts("jumpe ]");
                    break;
                case 6:
                    puts("ptrincr >");
                    break;
                case 7:
                    puts("ptrdecr < ");
                    break;
                case 255:
                    std::cerr << "syntax error" << std::endl;
                    return -114;
            }
        }
    }
    std::cout << "Hello" << std::endl;
    
    return 0;
}