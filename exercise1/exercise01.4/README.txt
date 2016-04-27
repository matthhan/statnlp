This is our implementation of exercise 1.4.

-------------------How to run------------------------------
We did preprocessing with a simple bash script, which is called script.sh and
can be executed like "./script.sh <filename>". After this preprocessing, the
file is formatted such that every line contains exactly one word.
The actual program can be compiled by simply running 'make' and this will
produce a file program.out, which can be executed like "./program.out -n <word
number> -f <filename>".
E.g. for the example file our whole soloution can be run as "./script.sh
alice.txt;make;./program.out -n 1000 -f preprocessed.txt".
--------------------------Description of program--------------
The main file "exercise1.04.cc" parses the command line argument, reads the
text, finds the n most frequent words and then outputs the text with frequent
words intact but infrequent word replaced by <UNK>.
The dictionary was implemented as a HashTable, i.e. If one wants to find the
index for a word, one can simply compute the value of the Hash function and
possibly check for collision 
(But collisions are not usually the case if the
Hash table is large enough. Care was taken to choose the size of the Hash
Table so that this does not occur).
To find the word for a given index, one can simply take the value at that
position in the vector, which happens in constant time. 

To keep track of the counts, we wrote a class occurence_counter, which uses 
a std::map data structure. Thus, updating or checking the count for a given 
index is performant. However, getting a List
of the top n values requires linear time. This should not be a problem as
this action is usually carried out at most once.

