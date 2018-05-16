# Instituto de Computação - UFAL

## Data Structure Project - Huffman

#### Professor: [Márcio Ribeiro](https://sites.google.com/a/ic.ufal.br/marcio/home)

>**Group** :
>>[Lucas Agra](https://github.com/lucasagra)   
>>[Phyllipe Bezerra](https://github.com/pmba)  
>>[Thiago Tenório](https://github.com/thitcc)

### Huffman: 
 
#### File Compression

1. The first step, after opening the desired file, is to create a ``Hash Table``
to store the bytes that compose the file. The table will have 256 positions, one
for each ASCII table encoding.

   >_The bytes are placed in a structure, called **Element**, each element will store 
its byte representative, frequency of occurrence and shortly thereafter will
store the new bit path (compressed byte)._
   >> Note: _each position on the table will point to an Element._

2. After building the Hash Table, it is primordial to enqueue all its elements
in a ``Priority Queue``, from the smallest to the highest occurrence frequency.
The queue will point to _Binary Trees_, now each Element will turn into
Binary Trees with pointers to left and right, initially null (leaf).

   > _Each Binary Tree will also have a pointer to the next one (following the idea of 
the priority queue)._
   >> Note: _the bit path will not be used on the Binary Trees._
   
3. Soon after building the Priority Queue, we arrived at the crux of file compression,
creating a Binary Tree - ``Huffman Tree`` - from the Priority Queue. To do this, it is
necessary to create a Binary Tree (Parent) with its representative being the character
'*', then the two lowest occurring leaves of the priority queue are removed, these leaves
will be respectively the left child and right child of the new binary tree created, the 
frequency of the new Binary Tree will be the sum of the frequencies the left and right 
child. The Binary Tree it is then enqueued in the Priority Queue.

   > _This will be a recursive function, the stop will happen when the current Binary Tree
checked has its pointer to the next one being null._  
   >> Note: _If there is already a byte representing the '*' character, then the parent's 
rep will have a escape character before, just as if there is already a byte representing
the escape character._
    
4. With the Huffman Tree created, we can now create the ``Bit Paths`` that will represent
each byte. To do this we will recursively traverse the tree by the Depth-first search
method.

   > _Before we start traversing the tree, we allocate a **Stack** to save bits. The idea
is that when going to the left, it pushes '0' in the stack, when going to the right pushes
'1' in the stack. Upon returning to the previous function, pop the element pushed previously
on the stack._
   >> Note: _an interesting aspect is that the way we create this tree, every leaf is a byte
of the file. This way it is easy to establish a stop condition for recursion._

5. As we walk through the tree, on reaching a leaf, we go to the position in the hash table
which the byte of that leaf represents, we push each node of the separate stack into the
stack within the structure of that element's position (Path). This method gives us the possibility
to save the byte already compressed in its respective position in the hash table.

   > _We chose to use a stack to let the manipulation of the paths while traversing tree easier
because while the tree is traversed, the binaries (0 or 1) are pushed on the stack, however in 
this way they are reversed, but by copying the stack in the path of each byte in the hash table, 
it reverses again, and the inverse of the reverse is the original path._

6. Now let's get the 2 first bytes of the ``Header``. For this we need to have the size of the trash (how much
is missing for the last byte to have 8 bits) and the size of the tree (number of nodes). Having
this, we proceed to get these 2 bytes with shiftbits and bitwise operations.

7. In the last step we start the compression creating a new file. First we write the 2 bytes got from the last step,
which represents the trash and tree size, after that we run a recursive function to print all the preoder bytes in the file.
Now that the header is done, we start to read the file to be compressed. As we go through the file, 
reading byte by byte, we go to the position in the hash table that represents the byte read, we take the stack that 
stores the compressed byte and check 1 by 1, when the stack is finished it means that byte was compressed.
Back in the last step, we managed to use the bits of an integer byte to deal with the bits read from the stack,
as it was like a Queue, through bitwise operations.
When the 'Queue' reaches 8 or more bits, we remove the oldest 8 bits and print its respective char in the file.
After the reading of the file is done, if there is remaining bits in the 'Queue', we insert bits 0's until this last 
byte is complete, then it's written in the file.

   > Note: _we read the file again because in this algorithm, we do not save the sequence that each byte
appears._
   
#### File Decompression

1. The first step, after opening the desired file, is to save the total bytes of the file. We'll need 
that because this algorithm read up to the next-to-last byte of the file.

2. Then the first 2 bytes (16 bits) of the head must be read, with the first 3 bits representing the
size of the trash, and the remaining 13 bits representing the size of the huffman tree.

   >_Shortly thereafter, we remove from the total file size the 2 bytes read and the size of the tree
(because the tree nodes are written in preorder in the header)._

3. Now having the tree in the file, and the size of it, we can proceed with the construction of the
``Huffman Tree``. For this we use a recursive function that reads byte per byte from the preorder tree
included in the header.

   >_The stop condition is relative to the size of the tree, while the size is greater than 0, the
function continues to execute._

4. With the tree ready, it's time to start decompressing. In this algorithm, we reallocate the string
containing the file name in order to remove the .huff extension.

5. In the decompression process, we read first to the last but one byte. For each read byte, go bit by bit,
traversing the tree, if the bit is 1, go right, if 0 goes left. At the moment the current node is a leaf,
write the byte of its representative in the new file and go back to the root of the tree.

6. Then we read the last byte. It's basically the same process from the previous one, the only difference is that the loop is managed by the size of the trash.
