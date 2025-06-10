#include <sstream>
#include <fstream>
#include "../include/FileService.h"
#include "../include/Macros.h"
#include "../include/ShellService.h"

bool FileServices::doesNonEmptyFileExist(std::string path) {
    std::ifstream file(path);
    return file.good() && file.peek() != std::ifstream::traits_type::eof();
};

void FileServices::emptyFile(std::string path) {
    std::stringstream cmd;
    cmd << CAT_PATH << " " << NULL_PATH << " > " << path;
    ShellService::exec(cmd.str().c_str());
};

void FileServices::createOrOverwriteFile(std::string path, std::string content) {
    std::stringstream cmd;
    cmd << ECHO_PATH << " " << content << " > " << path;
    ShellService::exec(cmd.str().c_str());
};