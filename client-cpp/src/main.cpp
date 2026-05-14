// Author: Nathan Metens
// Front end client app for Storage Drive.
// Main client program.
#include "http_requests.h" // Include the upload, list, and download http methods

// Main method taking an argument count and an argument vector of strings from terminal.
// Check for correct number of arguments and wether the command is supported.
int main(int argc, char** argv) {

   if (argc < 2) {
        usage();
        return 0;
    }

    std::string command = argv[1]; // upload, list, download

    // Filter commands for correct http request/response.
    if (command == "list" && argc >= 2) 
        list_files();
    else if (command == "upload" && argc == 3)
        upload_file(argv[2]);
    else if (command == "download" && argc == 3) 
        download_file(argv[2]);
    else usage();

    return 1;
}
