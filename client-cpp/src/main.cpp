#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Usage: ./storagedrive_client <file_path>\n";
        return 0;
    }

    std::string file_path = argv[1];

    std::string command = 
        "curl -F \"file=@" + file_path + "\" http://127.0.0.1:3000/upload";

    std::cout << "Uploading file: " << file_path << "\n";

    int result = std::system(command.c_str());

    if (result == 0) std::cout << "\nUpload complete.\n";
    else std::cout << "\nUpload failed.\n";

    return result;
}
