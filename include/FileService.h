#ifndef FILE_SERVICES_H
#define FILE_SERVICES_H

#include <string>

class FileServices {
    public:
    static bool doesNonEmptyFileExist(std::string);
    static void emptyFile(std::string);
    static void createOrOverwriteFile(std::string, std::string);
};

#endif