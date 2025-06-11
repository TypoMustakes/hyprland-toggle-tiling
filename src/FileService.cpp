#include <sstream>
#include <fstream>
#include "../include/FileService.h"
#include "../include/Macros.h"
#include "../include/ShellService.h"

bool FileService::doesNonEmptyFileExist(std::string path) {
    std::ifstream file(path);
    return file.good() && file.peek() != std::ifstream::traits_type::eof();
};

void FileService::emptyFile(std::string path) {
    std::stringstream cmd;
    cmd << CAT_PATH << " " << NULL_PATH << " > " << path;
    ShellService::exec(cmd.str().c_str());
};

void FileService::createOrOverwriteFile(std::string path, std::string content) {
    std::stringstream cmd;
    cmd << ECHO_PATH << " " << content << " > " << path;
    ShellService::exec(cmd.str().c_str());
};

void FileService::appendToFile(std::string path, std::string content) {
    bool fileNotEmpty = FileService::doesNonEmptyFileExist(path);
    std::stringstream cmd;
    if (fileNotEmpty) {
        cmd << ECHO_PATH << " \"" << "\n" << content << "\" >> " << path;
    } else {
        cmd << ECHO_PATH << " \"" << content << "\" >> " << path;
    }
    ShellService::exec(cmd.str().c_str());
};

void FileService::deleteNthLine(std::string path, int n) {
    std::vector<std::string> lines = readLines(path);

    if (n < 0 || n >= static_cast<int>(lines.size())) {
        // Out of bounds, do nothing
        return;
    }

    lines.erase(lines.begin() + n);

    std::ofstream file(path, std::ios::trunc);
    for (size_t i = 0; i < lines.size(); ++i) {
        file << lines[i];
        if (i != lines.size() - 1) {
            file << '\n';
        }
    }
}

std::vector<std::string> FileService::readLines(std::string path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
};