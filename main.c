#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>       // open()
#include <unistd.h>      // read(), write(), close()
#include <sys/types.h>   // types used in syscalls
#include <sys/stat.h>    // mode constants for open()

#define STATUS_SUCCESS 0
#define STATUS_ERROR -1
#define BYTE_AMOUNT_TO_READ 1
#define MAX_ARRAY_SIZE 256

// Forward declarations
int create_cyphertext(uint8_t* arrayS, char* filename_input, char* filename_output);
void swap_elements(uint8_t* array, char* key, uint8_t key_length);
void populate_array();
void print_array_hex();
// file operations
int open_file(char* filename); 
int write_byte_to_file(int fd, char* byte_to_write);
int read_byte_from_file(int fd, char* byte_to_read);
int close_file(int fd);


int main() {
    // vars declaration
    char* test_key = "Key"; uint8_t key_length = strlen(test_key);
    char* filename_input = "input.txt"; char* filename_output = "output.txt";
    uint8_t S[MAX_ARRAY_SIZE];
    // encryption/decryption
    populate_array(S);
    swap_elements(S,test_key,key_length);
    create_cyphertext(S,filename_input,filename_output);

    return STATUS_SUCCESS;
}

/**
*@brief encode input file byte by byte on basis of keystream
*@param array array with shuffled numbers 
*@return none
 **/
int create_cyphertext(uint8_t* arrayS, char* filename_input, char* filename_output) {
    //open files to read and write to
    int inputfile_fd = open_file(filename_input);
    int outputfile_fd = open_file(filename_output);
    int i = 0; int j = 0; uint8_t K = 0;
    char encrypted_byte; char* encrypted_byte_ptr = &encrypted_byte;
    char read_byte; char* read_byte_ptr = &read_byte;

    while(1) {
        int read_status = read_byte_from_file(inputfile_fd, read_byte_ptr);
        if(read_status == STATUS_ERROR) {
            printf("Error reading byte from file. Encryption terminated!\n");
            return STATUS_ERROR;
        }
        if(read_status == 0) {
            printf("End of file reached.\n");
            return STATUS_SUCCESS;
        }
        // further scrambling of state
        i = (i+1) % MAX_ARRAY_SIZE;
        j = (j+arrayS[i]) % MAX_ARRAY_SIZE;
        // swap values
        uint8_t temp = arrayS[i];
        arrayS[i] = arrayS[j];
        arrayS[j] = temp;
        // chose K to XOR the input byte with
        K = arrayS[(arrayS[i] + arrayS[j]) % MAX_ARRAY_SIZE];
        encrypted_byte = K ^ read_byte;
        
        write_byte_to_file(outputfile_fd,encrypted_byte_ptr);
    }



}

/**
*@brief swap elements of array around according to provided pseudocode
*@param array array with numbers 
*@param key string with key value
*@return none
 **/
void swap_elements(uint8_t* array, char* key, uint8_t key_length) {
    uint8_t j = 0;
    for(int i = 0; i < MAX_ARRAY_SIZE; i++) {
        j = (j + array[i] + key[i%key_length]) % MAX_ARRAY_SIZE;
        uint8_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/**
*@brief populate array with numbers from 0 - 255
*@param array empty array to populate 
*@return none
 **/
void populate_array(uint8_t* array) {
    for(int i = 0; i < MAX_ARRAY_SIZE; i++) {
        array[i] = i;
    }
}

void print_array_hex(uint8_t* array) {
    for(int i = 0; i < MAX_ARRAY_SIZE; i++) {
        printf("%x\n", array[i]);
    }
}

/**
*@brief open file with filename and create file descriptor
*@param filename name of file
*@return file descriptor
 **/
int open_file(char* filename) {
    int fd = open(filename, O_RDWR | O_APPEND);
    if(fd == STATUS_ERROR) {
        close(fd);
        printf("Error during file opening.\n");
        return STATUS_ERROR;
    }
    return fd;
}

/**
*@brief write to file with file descriptor
*@param fd filedescriptor of file to write to
*@param byte_to_write byte to be written to output after encryption
*@return STATUS SUCCESS or STATUS ERROR
 **/
int write_byte_to_file(int fd, char* byte_to_write) {
    int bytes_written = write(fd, byte_to_write, BYTE_AMOUNT_TO_READ);
    if(bytes_written == STATUS_ERROR) {
        close(fd);
        perror("Error while writing to file");
        return STATUS_ERROR;
    }
    return STATUS_SUCCESS;
}

/**
*@brief read one byte from file with file descriptor
*@param fd filedescriptor of file to write to
*@return STATUS SUCCESS or STATUS ERROR
 **/
int read_byte_from_file(int fd, char* byte_to_read) {
    int bytes_read = read(fd,byte_to_read,BYTE_AMOUNT_TO_READ);
    if(bytes_read == STATUS_ERROR) {
        perror("Error reading from file");
        return STATUS_ERROR;
    }
    return bytes_read;
}


/**
*@brief close file descriptor
*@param fd file descriptor of file to close
*@return STATUS SUCCESS or STATUS ERROR
 **/
int close_file(int fd) {
    int is_closed = close(fd);
    if(is_closed == STATUS_ERROR) {
        perror("Error during file closing");
        return STATUS_ERROR;
    }
    return STATUS_SUCCESS;
}