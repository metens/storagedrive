// Author: Nathan Metens
// Front end client app for Storage Drive.
// Main client program.
#include "http_requests.h" // Include the upload, list, and download http methods

// Main method taking an argument count and an argument vector of strings from terminal.
// Check for correct number of arguments and wether the command is supported.
int main(int argc, char** argv) {

    /* Three total arguments: 
     *      1 (the storage client executible), 
     *      2 (the http command to the server), 
     *      3 (the file to upload to or download from the rust server).
     */
    if (argc < 3 && strcmp(argv[1],"list") != 0 ) {
        std::cout << "Usage:\n";
        std::cout << "./storagedrive_client upload <file>\n";
        std::cout << "./storagedrive_client list\n";
        std::cout << "./storagedrive_client download <file>\n";
        return 0;
    }

    std::string command = argv[1]; // upload, list, download

    // Filter commands for correct http request/response.
    if (command == "upload") 
        upload_file(argv[2]);
    else if (command == "list") 
        list_files();
    else if (command == "download") 
        download_file(argv[2]);
    else std::cout << "Unknown command." << std::endl;

    return 1;
}
