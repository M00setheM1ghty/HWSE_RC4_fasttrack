#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void swap_elements();
void populate_array();
void print_array();

int main() {
    char* test_key = "imatestkey";
    uint8_t S[256];
    populate_array(S);
    swap_elements(S,test_key);
    print_array(S);
    printf("%d\n", S[143]);
    return 0;
}

/**
*@brief swap elements around according to provided pseudocode
*@param array array with nums
*@param key string with key
*@return none
 **/
void swap_elements(uint8_t* array, char* key) {
    uint8_t j = 0;
    for(uint8_t i = 0; i < 255; i++) {
        j = (j + array[i] + key[i%(sizeof(key))]) % 256;
        uint8_t temp = array[i];
        array[i] = j;
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

void print_array(uint8_t* array) {
    for(int i = 0; i < 256; i++) {
        printf("%d\n", array[i]);
    }
}