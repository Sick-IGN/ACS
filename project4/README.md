# Design

The data structure I will be designing has a view goals
- Bidirectional encoding/decoding (encoded -> plaintext, and plaintext -> encoded)
- Existance check
- Prefix matching
- Be capable of utilizing SIMD instructions to speedup search

All of these must be accomplished efficiently.

My intial thoughts on this design was the use a hash table, as they are known for being extremely effective and efficient data storage methods.
However, hash tables cannot efficiently performance prefix scanning. This operation would be of O(n) time complexity, as every value must be checked.
There is no way to actively reduce the search space as the search progresses, and no way to just hash part of the string: hashing simply does not work that way.

After some research, I decided upon a trie, which is a type of k-ary tree which is optimized for storing and querying strings.
However, tries are not easily capable of performing encoded->plaintext decoding, as they are structured around the plaintexts characters.
This lead me to my implemented solution, which uses both.
Given an encoded value, you can simply query the hash table to return it, which is an O(1) access. If you have to search for an index based on a string, you query the trie, which is has an O(L) time complexity, where L is the length of the string.|

This does come with some downsides, however. Most notably is the inability to effectively utilize SIMD instructions for speedup.
There are only L comparisons necessary (L being the length of the string you are looking up), and they must be done in order. The first character must be checked before the second one can. 
This type of linear comparisons do not significantly benefit from SIMD, which is most powerful with easily parallelizable instructions, like mass comparisons or masss arithmetic.
These mass arthimetic instructions are not utilized by my implementation.
However, I still will be implementing an SIMD search/scan, but I predict it would likely be slower due to overhead.
This is not really that big of a downside though, as the trie I have implemented already allows for efficient prefix scanning and existance checking.
I hope my analysis on the strengths/weaknesses of SIMD instructions and why they are not effective in my implementation will be sufficient for the credit.

# Implementation and Analysis

Encoding: 
  I implemented two encoding functions; one with multithreading and one without. To load the entire given file, the single threaded load function took 152 seconds, while the multithreaded load function using 8 threads took 26 seconds. This is about a 6x speedup, which is around the expected for a function using 8 threads.

Dumping the saved Dict to a file:
  I implemented two functions, "GenDictFile" for singlethreaded and "threadedGenFile" for multithreaded. These functions take everything stored in the Dict datastructure and dump it to a file, for ease of transfer. Interestingly, the multithreaded version took 1.75x longer then the singlethreaded version. This is likely due to the fact that writing to files isn't an easily multithreadable. Therefore, this multithreaded operation is likely being bottlenecked by the writing. The extra slowdown comes from the overhead setting up multithreading causes. Just cause the function is looping through the map 8 or 16 times at once, only one write operation happens at a time due to the mutex preventing multiple writes at a time (to prevent race conditions).

Encoding and Decoding a file:
  These functions loop through a file, and replace encoded values with the associated string, or vice versa. Multithreading is used to read from the input file more rapidly, and this leads to ~6-7x increase for both, as expected.

Generate pairs:
  This function generates a pair. It converts a line "str" to "index str". Similarly to dumping saved dict to a file, the multithreading provides no speed increase. This is due to again, primarily write operations.

Searching:
  I implemented multiple searching functions. First, one that searches for a string in the code, one that searches for a prefix in the code. Then, I implemented find-in-file functions; exact match, exact with SIMD, prefix scanning, and prefix with SIMD. For all the find-in-file functions, they run at around the same speed. This is likely due to reading I/O operations being a significant bottleneck. Searching/prefix scanning from a string in the code is very efficient though, magnitudes faster then the read-from-file operations, further suggesting that I/O operations are the bottleneck. 


# Conclusions

One major conclusion from my experiments is how annoying write operations are to deal with. While reading can, to some extent, be multithreaded, writing cannot be. It is possible that I just couldn't figure it out, but I do not believe so. 
This is significant, as it shows how I/O operations should optimally be avoided unless absolutely necessary.
Along with writes being slow, a lot of the potential optimizations from my datastructure are removed simply by the necessity of reads. When the bottleneck is reading a file, it doesn't matter how fast the datastructure is. Both encoded and decoded searches are equal speed when the entire file needs to be read.
If no read operations are necessary however, then my implemented datastructure provides a significant lookup benefit to a simple array.

Another important note is on SIMD instructions. Depending on implementation, they are not always beneficial, and this isn't necessarily a bad thing. For example, my Trie implementation allows for efficient searching and prefix searching with very few comparisons. A different implementation that has more comparisons or arithmetic would likely benefit more from SIMD instructions, but it might also be slower despite the SIMD optimizations.

Overall, when implemented with consideration, dictionaries, encoding, SIMD and all other things can definitely provide benefits, however they are not always beneficial.