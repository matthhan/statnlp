ngram-count  -text ./$1 -order $2 -lm temp.lm 
ngram -lm temp.lm -ppl $1
rm temp.lm
