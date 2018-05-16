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

#endif //HUFFMAN_PROJECT_DECIMAL_BINARY_H
