This is our solution for exercise 9.2

The program prints usage instructions. To calculate per on the provided data, do:

./program.out -r ref -h hyp -p

The actual interesting part happens in the functions wer and per respectively:

 * To compute WER we use dynamic programming. Implementation is done with an array (not memoization)
 * To compute PER we insert all of the words in both sentences into a set so we can iterate over them. Then we sum up the absolute differences of occurence frequencies and plug the result into the formula for PER as described in Popovic, Ney 2007.

Disclaimer: We have reused some code for file io and parameter passing from previous exercises. In addition, we have already implemented WER calculation in another course at i6 (Automatic Speech Recognition). This implementation is mostly the same as our old one from that course.
