#pragma once
#define nr_input_paths 10

//everything is accessible from both gui and cmd
void display_instructions_bash();
bool argument_verification(int argc, char** argv);

bool compress_huf(char* path_output, char* output_name);
bool decompress_huf(char* path_input, char* path_output, char* output_name);

//this function will always have correct parameters
void very_last_step(char* operation, char* algorithm, short nr_paths, char** paths_input, char* path_output, char* output_name);
