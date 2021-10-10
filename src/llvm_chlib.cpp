#include "base_teigi.hpp"

    std::string plus_value="加算";
    std::string minus_value="減算";
    std::string outkun="出力";
    std::string readinputkun="入力";
    std::string jumps="飛行前";
    std::string jumpe="飛行後";
    std::string ptrincr="参照加";
    std::string ptrdecr="参照減";
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
