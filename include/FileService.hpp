#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <string>
#include <vector>

class FileService {
    public:
    static bool doesNonEmptyFileExist(std::string);
    static void emptyFile(std::string);
    static void createOrOverwriteFile(std::string, std::string);
    static void appendToFile(std::string, std::string);
    static void deleteNthLine(std::string, int);
    static std::vector<std::string> readLines(std::string);
};

#endif