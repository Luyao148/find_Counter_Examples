#include <fstream>
#include <memory>
#include <mutex>
#include <string>

const std::string FILE_NAME = "output.txt";
constexpr int BUFFER_SIZE = 10000;

class FileWrite {
  public:
    static std::unique_ptr<FileWrite> getFileWritrHandle();
    FileWrite()=delete;
    FileWrite(const std::string& _file_name);

    FileWrite(const FileWrite&) = delete;
    FileWrite& operator=(const FileWrite&) = delete;

    FileWrite(FileWrite&&) = delete;
    FileWrite operator=(FileWrite&&) = delete;

    void writeData(const std::string& _s);

    ~FileWrite();
  private:
    std::ofstream ofs;
    std::string buffer;
    std::mutex mtx;
};