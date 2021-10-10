find_package(LLVM REQUIRED)
add_executable(llvm_bf llvm_bf.cpp llvm_chlib.cpp llvm_lplib.cpp)
target_link_libraries(llvm_bf LLVM)