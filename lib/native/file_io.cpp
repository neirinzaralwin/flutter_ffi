#include <fstream>
#include <string>
#include <cstring> // For strlen and memcpy

extern "C"
{

    // Function to write a string to a file.
    // Returns 0 on success, -1 on failure.
    int writeToFile(const char *filePath, const char *content)
    {
        std::ofstream outputFileStream(filePath);
        if (!outputFileStream.is_open())
        {
            return -1; // Failure to open file
        }
        outputFileStream << content;
        outputFileStream.close();
        return 0; // Success
    }

    // Function to read content from a file.
    // Allocates memory for the content (caller must free it).
    // Returns the length of the content on success, -1 on failure.
    // The content is stored in the outContent pointer.
    int readFromFile(const char *filePath, char **outContent)
    {
        std::ifstream inputFileStream(filePath);
        if (!inputFileStream.is_open())
        {
            return -1; // Failure to open file
        }

        // Get file size
        inputFileStream.seekg(0, std::ios::end);
        size_t fileSize = inputFileStream.tellg();
        inputFileStream.seekg(0, std::ios::beg);

        // Allocate memory (plus null terminator)
        *outContent = new char[fileSize + 1];
        if (*outContent == nullptr)
        {
            return -1; // Memory allocation failure
        }

        // Read content
        inputFileStream.read(*outContent, fileSize);
        (*outContent)[fileSize] = '\0'; // Null-terminate
        inputFileStream.close();

        return static_cast<int>(fileSize); // Return length
    }

    // Function to free the memory allocated by readFromFile.
    void freeMemory(char *memoryToFree)
    {
        delete[] memoryToFree;
    }
}