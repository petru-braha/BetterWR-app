#include <filesystem>
#include <iostream>
#include <cstring>

#include "middle.h"
#include "../../admin/pack.h"
//#include "../../admin/algorithms/huf.h"
//#include "../../admin/algorithms/lzw.h"
#define MAX 300
void show_saved_size(size_t originalSize, size_t encodedSize){
    size_t bytesSaved = originalSize - encodedSize;
    std::cout << "Original size: " << originalSize << " bits" << " (" << originalSize / 8 << " bytes).\n";
    std::cout << "Encoded size: " << encodedSize << " bits" << " (" << encodedSize / 8 << " bytes).\n";
    std::cout << "Bits saved: " << bytesSaved << " bits" << " (" << bytesSaved / 8 << " bytes).\n";
    std::cout << '\n';
}

bool compress_huf(char* path_output, char* output_name) //the temp file is built, ik its location => encoding, final output
{
    /*
    FILE* input = fopen(temp_location, "rb");
    FILE* output = fopen(strcat(path_output, output_name), "wb");
    if (input == nullptr)
    {
        printf("error - compress_huf : missing temp file.\n");
        fclose(input);
        return false;
    }

    ///let's assume that everything is in ASCII
    char to_be_encoded[MAX] = { 0 };
    size_t bytes_read = 0;
    bool first_exe = true;
    int* encoded_text = nullptr;

    string binaryData(to_be_encoded, bytes_read);
    node* root = build_huf_tree(binaryData);
    string encodedString = huf_encode_string(root, binaryData);
    string output_text__ = write_encoded_ascii(encodedString); //cu info necesare

    // write extra details
    char treeInfo[MAX]; int treeFreq[MAX], treeSize = 0;
    create_tree_string(root, 1, treeInfo, treeFreq, treeSize);

    fwrite(&treeSize, sizeof(int), 1, output);
    for(int i = 1; i <= treeSize; ++i)
        fwrite(&treeFreq[i], sizeof(int), 1, output);
    for (int i = 1; i <= treeSize; ++i)
        fwrite(&treeInfo[i], sizeof(char), 1, output);
    int bitlength = encodedString.size();
    fwrite(&bitlength, sizeof(int), 1, output);
    ///write important part
    fwrite(textToOutput.c_str(), sizeof(char), textToOutput.size(), output);

    show_saved_size(bytes_read * 8, textToOutput.size() * 8);
    fclose(input);
    fclose(output);
    return true;
    */
    return true;
}

bool decompress_huf(char* path_input, char* path_output, char* output_name)
{
/*    std::filesystem::path p_path(path_input);
    std::error_code ec;
    if (std::filesystem::path(p_path, ec).extension().string().c_str() != "huf"){
        std::cout<<"error - decompression: wrong file extension / selected algorithm.\n";
        return false;
    }

    FILE* input  = fopen(path_input, "rb");
    FILE* output = fopen(strcat(path_output, output_name), "wb");
    if (output == nullptr || input == nullptr) {
        printf("error - decompression: invalid file paths.\n");
        fclose(input); fclose(output);
        return false;
    }

    // Citim datele din input si le punem intr-un buffer
    const int BUFFER_SIZE = 30000;  // adjustare manuala
    char buffer[BUFFER_SIZE];

    // Intai recuperam informatiile despre arborele Huffman
    char treeInfo[MAX];
    int treeFreq[MAX];
    int treeSize = 1;
    int bitlength;

    fread(&treeSize, sizeof(int), 1, input);

    for (int i = 1; i <= treeSize; ++i)
    {
        fread(&treeFreq[i], sizeof(int), 1, input);
    }

    for (int i = 1; i <= treeSize; ++i) {
        fread(&treeInfo[i], sizeof(char), 1, input);
    }

    fread(&bitlength, sizeof(int), 1, input);

    // Citim restul continutului, care reprezinta de fapt textul encodat
    size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, input);
    if (bytesRead <= 0) {
        printf("Error reading input file\n");
        fclose(input);
        exit(1);
    }

    // Crearea unui string din bufferul citit din fisier
    string binaryData(buffer, bytesRead);

    node* rootNode = reconstructTree(treeSize, 1, treeInfo, treeFreq); //reconstruct huffman tree
    string codes = ASCIIToBinary(binaryData, bitlength); // ASCII => string of bits => decode

    // Realizarea decodarii Huffman si scrierea textului decodat in fisier
    string decodedOutput = "";
    HuffmanDecode(rootNode, codes, decodedOutput);
    fwrite(decodedOutput.c_str(), sizeof(char), decodedOutput.size(), output);

    fclose(input);
    fclose(output);*/
    return false;
}

void display_instructions_bash() {
    std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>\n";
    std::cout << "Check for syntax errors:\n";
    std::cout << "operations: 'compress' / 'decompress'\n";
    std::cout << "algorithms: 'HUF' / 'LZW'\n";
    std::cout << "check if the number of paths given is < 10 and is equal with nr_input_files.\ncheck if the paths are valid.\n\n";
}
bool verify_options(int argc, char** argv, int& nr){
    if (argc < 7)
    {
        std::cout << "Usage: " << "<operation> <algorithm> <nr_input_files> <input_file_paths> <output_path> <output_name>\n";
        return false;
    }

    if (strcmp(argv[1], "compress") && strcmp(argv[1], "decompress"))
    {
        std::cout << "error: invalid first argument.\n\n";
        display_instructions_bash();
        return false;
    }

    if (strcmp(argv[2], "HUF") && strcmp(argv[2], "LZW"))
    {
        std::cout << "error: invalid second argument.\n\n";
        display_instructions_bash();
        return false;
    }

    nr = 0;
    for (int i = 0; argv[3][i]; i++)
        nr = nr * 10 + (argv[3][i] - '0');
    if (nr + 6 != argc || nr <= 0 || nr > 10)
    {
        std::cout << "error: invalid third argument.\n\n";
        display_instructions_bash();
        return false;
    }
    return true;
}
bool verify_paths(int argc, char** argv, int& nr){
    for (int i = 0; i < nr; i++)
    {
        if (std::filesystem::exists(argv[i + 4]) == 0)
        {
            std::cout << "error: invalid input_path argument.\n\n";
            display_instructions_bash();
            return false;
        }

        //make sure that the paths of folders are correctly written
        size_t last_index_path = strlen(argv[i + 4]) - 1;
        //std::filesystem::path temp_path = argv[i + 4];
        if(std::filesystem::is_directory(argv[i + 4]) && argv[i + 4][last_index_path] != '/')
        {
            argv[i + 4][++last_index_path] = '/';
            argv[i + 4][++last_index_path] = '\0';
        }
    }


    if (std::filesystem::exists(argv[argc - 2]) == 0) //has to be a folder
    {
        std::cout << "error: invalid output_path argument.\n\n";
        display_instructions_bash();
        return false;
    }
    size_t last_index_path = strlen(argv[argc - 2]) - 1;
    if(argv[argc - 2][last_index_path] != '/')
    {
        argv[argc - 2][++last_index_path] = '/';
        argv[argc - 2][++last_index_path] = '\0';
    }

    for (size_t i = 0; i < strlen(argv[argc - 1]); i++)
    {
        if (argv[argc - 1][i] < 'A' || argv[argc - 1][i] > 'z' || (argv[argc - 1][i] > 'Z' && argv[argc - 1][i] < 'a'))
        {
            std::cout << "error: invaid name.\n\n";
            return false;
        }
    }
    last_index_path = strlen(argv[argc - 1]) - 1;
    if(argv[argc - 1][last_index_path] != '/')
    {
        argv[argc - 1][++last_index_path] = '/';
        argv[argc - 1][++last_index_path] = '\0';
    }
    return true;
}
bool argument_verification(int argc, char** argv){
    int nr = 0;
    if(verify_options(argc, argv, nr) && verify_paths(argc, argv, nr))
        return true;
    return false;
}


void very_last_step(char* operation, char* algorithm, short nr_paths, char** paths_input, char* path_output, char* output_name)
{
    if (strcmp(operation, "compress") == 0)
    {
        build_tar(nr_paths, paths_input);
        if (strcmp(algorithm, "HUF") == 0)
            //compress_huf(path_output, output_name);
        if (strcmp(algorithm, "LZW") == 0);
//            compress_lzw(path_output, output_name);
    }
    else
    {
        for(int i=0; i < nr_paths; i++)
        {
            if (strcmp(algorithm, "HUF") == 0)
                //decompress_huf(paths_input[i], path_output, output_name);
            if (strcmp(algorithm, "LZW") == 0);
                //decompress_lzw(paths_input[i], path_output, output_name);
            decompose_tar(path_output, output_name);
        }
    }

    //if(remove("files/temp.tar"))
        //std::cout<<"error: temporary file not deleted.\n";
}
