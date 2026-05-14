#include <iostream>
#include <cstdlib>
#include <string>
#include <cpr/cpr.h> // docs: https://docs.libcpr.dev/advanced-usage.html#other-request-methods

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

void upload_file(const std::string& filepath) {
    cpr::Response r = 
        cpr::Post(
            cpr::Url{"http://127.0.0.1:3000/upload"},
            cpr::Multipart{
                {"file", cpr::File{filepath}}
            }
        );

        std::cout << "Status Code: " << r.status_code << std::endl;
        std::cout << r.text << std::endl;
}

void list_files() {
    std::string url = "http://127.0.0.1:3000/files";
    
    cpr::Response r = 
        cpr::Get(cpr::Url{url});

    std::cout << r.text << std::endl; // JSON text string
    return;
}

void download_file(char* file) {

}

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "Usage:\n";
        std::cout << "./storagedrive_client upload <file>\n";
        std::cout << "./storagedrive_client list\n";
        std::cout << "./storagedrive_client download <file>\n";
        return 0;
    }

    std::string command = argv[1];

    if (command == "upload") 
        upload_file(argv[2]);
    else if (command == "list") 
        list_files();
    else if (command == "download") 
        download_file(argv[2]);
    else std::cout << "Unknown command." << std::endl;


    /*std::string file_path = argv[1];

    std::string command = 
        "curl -F \"file=@" + file_path + "\" http://127.0.0.1:3000/upload";

    std::cout << "Uploading file: " << file_path << "\n";

    int result = std::system(command.c_str());

    if (result == 0) std::cout << "\nUpload complete.\n";
    else std::cout << "\nUpload failed.\n";

    test();*/

    //return result;
    return 0;
}
