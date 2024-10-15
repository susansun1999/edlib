#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <chrono>  // For timing
#include "edlib.h"

using namespace std;
struct pointer_w_length{
	char* buffer;
	unsigned length;
};


// Function to read file content starting from the second line
pointer_w_length generateBuffer(const char* filename) {
    // Open the file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return pointer_w_length();
    }

    // Skip the first line
    string firstLine;
    getline(file, firstLine);  // Read and discard the first line

    // Read the rest of the file into a string
    string remainingContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    pointer_w_length pwl;
    pwl.length = remainingContent.size();
    
    // cout << "size() = remainingContent.size() = " << remainingContent.size() << endl;
    // Allocate memory for const char* array
    pwl.buffer = new char[remainingContent.size() + 1];  // +1 for null terminator
    strcpy(pwl.buffer, remainingContent.c_str());  // Copy the remaining content into the buffer

    pwl.buffer[pwl.length - 1] = '\0';
    pwl.length -= 1;
    // Return the buffer (which will be treated as const)
    return pwl;
}

int main(int argc, char* argv[]) {
    // Check if a file name is provided
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <target> <query>" << endl;
        return 1;
    }

    // Generate the buffer starting from the second line
    pointer_w_length refer_pwl = generateBuffer(argv[1]);
    pointer_w_length read_pwl = generateBuffer(argv[2]);


    cout << "read length: " << read_pwl.length << endl;
    cout << "reference length: " << refer_pwl.length << endl;
    if (refer_pwl.buffer == nullptr || read_pwl.buffer == nullptr) {
        return 1;  // Error in file handling
    }

    // Output the content
//    cout << "File content starting from the second line:\n" << fileContent << endl;

    // Clean up
    const char* query = read_pwl.buffer;
    const char* target = refer_pwl.buffer;
    auto start = std::chrono::high_resolution_clock::now();
    EdlibAlignResult result = edlibAlign(query, read_pwl.length, target, refer_pwl.length, edlibDefaultAlignConfig());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    
    if (result.status == EDLIB_STATUS_OK) {
        printf("Edit Distance = %d\n", result.editDistance);
    }
    edlibFreeAlignResult(result);

    delete[] read_pwl.buffer;
    delete[] refer_pwl.buffer;
    
    return 0;
}

