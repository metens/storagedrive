#include <iostream>
#include <cstdlib>
#include <string>
#include <cpr/cpr.h>

int test() {
    /*
    * C++ Requests: https://github.com/libcpr/cpr?utm_source
    */

    std::string url = "https://nathanmetens.dev";
    
    cpr::Response r = 
        cpr::Get(cpr::Url{url},
        cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
        cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    std::cout << r.status_code << std::endl;              // 200
    std::cout << r.header["content-type"] << std::endl;   // application/json; charset=utf-8
    std::cout << r.text << std::endl;                     // JSON text string
    return 0;
}

int main(int argc, char** argv) {

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

    test();

    return result;
}
