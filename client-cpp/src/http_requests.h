// Author: Nathan Metens
// Front end client app for Storage Drive.
// HTTP request methods library.
#include <iostream>
#include <cstdlib>
#include <string>
#include <cpr/cpr.h> // docs: https://docs.libcpr.dev/advanced-usage.html#other-request-methods
#include <fstream>

// Upload a file to the rust server.
void upload_file(const std::string& filepath) {
    /*
     * C++ Requests: https://github.com/libcpr/cpr?utm_source
     */
    cpr::Response r = 
        cpr::Post(
            cpr::Url{"http://127.0.0.1:3000/upload"}, // upload api endpoint
            cpr::Multipart{
                {"file", cpr::File{filepath}}
            }
        );

    // Check status:
    if (r.status_code == 200) std::cout << "Upload successful\n";
    else std::cout << "Upload failed. Status: " << r.status_code << std::endl;

    return;
}

// List the files in the server:
void list_files() {
    std::string url = "http://127.0.0.1:3000/files"; // Rust files directory
    
    cpr::Response r = 
        cpr::Get(cpr::Url{url});

    if (r.status_code == 200) {
        std::cout << "Files on server:\n";
        std::cout << r.text << std::endl; // plain text list of files
    } else
        std::cout << "Failed to list files on server. Status: " << r.status_code << std::endl;

    return;
}

// Download the file into the rust api.
void download_file(const std::string& filename) {
    std::string url = "http://127.0.0.1:3000/download/" + filename;

    cpr::Response r = 
        cpr::Get(cpr::Url{url});

    if (r.status_code != 200)
        std::cout << "Download failed\n";
    else {
        // Create the file, write the contents, close file, and output confirmation.
        std::ofstream file(filename, std::ios::binary); // open files in binary mode
        file.write(r.text.c_str(), r.text.size());
        file.close();
        std::cout << "Downloaded: " << filename << std::endl;
    }

    return;
}
