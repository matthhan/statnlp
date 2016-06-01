#/bin/bash
ngram-count  -text ../tc-star -order $1 -lm temp.lm -kndiscount$1
ngram -lm temp.lm -ppl ../tc-star

