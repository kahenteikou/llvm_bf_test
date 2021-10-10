find_package(LLVM REQUIRED)
add_executable(llvm_bf llvm_bf.cpp llvm_chlib.cpp llvm_lplib.cpp llvm_addzissou.cpp llvm_ptraddzissou.cpp llvm_moji.cpp)
target_link_libraries(llvm_bf LLVM)