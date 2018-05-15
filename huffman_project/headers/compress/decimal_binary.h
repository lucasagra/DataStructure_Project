//
// Created by Lucas on 21-Apr-18.
//

#ifndef HUFFMAN_PROJECT_DECIMAL_BINARY_H
#define HUFFMAN_PROJECT_DECIMAL_BINARY_H

int is_bit_set (unsigned int integer, int i) {

	unsigned int mask = 1;
	mask = mask << (unsigned int)i;
	return (mask & integer);

/* Checks if the bit from the unsigned int integer
 * on the position i is set. If true, returns 2^i,
 * else returns 0
 */
}

int binary_pow (int shift) {

	return ((unsigned int)1 << (unsigned int)shift);

	//Returns 2 to the power of shift
}

int binary_double (unsigned int bin) {

	return (bin << (unsigned int)1);

	//Multiplies an int by 2
}

int binary_half (unsigned int bin) {

	return (bin >> (unsigned int)1);

	//Divides an int by 2
}

int* char_to_binary_int(unsigned char c) {

	int i, j;
	int *binary = malloc(sizeof(int) * 8);

	for (i = 0, j = 7; i < 8; j--, i++) 
	{
		if (is_bit_set(c, i))
		{
			binary[j] = 1;
		}
		else
		{
			binary[j] = 0;
		}
	}

	return binary;

    // Receives a byte as a char and returns its binary value as an array of int
}

unsigned char* int_to_binary_char(unsigned int integer, int num_bits) {

	int i;
	int j = num_bits-1; // Last position of string

	unsigned char *binary = malloc(sizeof(char) * num_bits);

	for (i = 0; i < num_bits; i++)
	{
		if (is_bit_set(integer, i))
		{
			binary[j] = '1';
		}
		else
		{
			binary[j] = '0';
		}
		j--;
	}

	return binary;

    /* Receives 4 bytes as an unsigned int and returns the
     * last num_bits binary values as an array of chars
     */
}

int binary_to_int (int* bin, int size, int i) {

    if (size >= 0)
    {

        if (bin[size]) // If element on position size is 1
        {
            return binary_pow(i) + binary_to_int(bin, --size, ++i);
            // Returns 2^i + decimal value from next bit
        }
        else // If element on position size is 0,
        {
            return binary_to_int(bin, --size, ++i);
            // returns 0 + decimal value from next bit
        }
    }

    return 0;

    /* Receives a sequence of binary numbers as an
     * array of int and return its value as an int
     */
}

int binary_char_to_int (unsigned char* string, int size, int i) {

    if (size >= 0)
    {
        if (string[size] == '1') // If element on position size is 1
        {
            return binary_pow(i) + binary_char_to_int(string, --size, ++i);
            // Returns 2^i + decimal value from next bit
        }
        else // If element on position size is 0,
        {
            return binary_char_to_int(string, --size, ++i);
            // returns 0 + decimal value from next bit
        }
    }

    return 0;

    /* Receives a sequence of binary numbers as an
     * string and return its value as an int
     */
}

#endif //HUFFMAN_PROJECT_DECIMAL_BINARY_H
