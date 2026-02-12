#include "FileWrite.h"
#include <cassert>
#include <cstdlib>
#include <ios>
#include <memory>
#include <mutex>
#include <stdexcept>

std::unique_ptr<FileWrite> FileWrite::getFileWritrHandle(){
    return std::make_unique<FileWrite>(FILE_NAME);
}

FileWrite::FileWrite(const std::string& _file_name):
    ofs(_file_name,std::ios::trunc | std::ios::out),
    buffer("")
{
    if(!ofs){
        throw std::runtime_error("Can not open the file.");
        std::abort();
    }
    buffer.reserve(BUFFER_SIZE*2);
}

void FileWrite::writeData(const std::string& _s){
    std::lock_guard<std::mutex> locker(mtx);
    buffer.append(_s);
    if(buffer.size()>BUFFER_SIZE){
        ofs << buffer;
        buffer.clear();
    }
}

FileWrite::~FileWrite(){
    if(!buffer.empty()){
        ofs<<buffer;
    }
    ofs.close();
}