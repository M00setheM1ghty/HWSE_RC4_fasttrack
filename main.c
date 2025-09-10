#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void swap_elements();
void populate_array();
void print_array_hex();

int main() {
    char* test_key = "Key"; uint8_t key_length = strlen(test_key);
    uint8_t S[256];
    populate_array(S);
    swap_elements(S,test_key,key_length);
    print_array_hex(S);
    //printf("%d\n", S[255]);
    return 0;
}

/**
*@brief swap elements of array around according to provided pseudocode
*@param array array with nums
*@param key string with key
*@return none
 **/
void swap_elements(uint8_t* array, char* key, uint8_t key_length) {
    uint8_t j = 0;
    for(int i = 0; i < 256; i++) {
        j = (j + array[i] + key[i%key_length]) % 256;
        uint8_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/**
*@brief populate array with numbers from 0 - 255
*@param array array of elements
*@return none
 **/
void populate_array(uint8_t* array) {
    for(int i = 0; i < 256; i++) {
        array[i] = i;
    }
}

void print_array_hex(uint8_t* array) {
    for(int i = 0; i < 256; i++) {
        printf("%x\n", array[i]);
    }
}