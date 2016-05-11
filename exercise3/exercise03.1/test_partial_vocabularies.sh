#!/bin/sh

echo "vocabulary_size,classifier_accuracy"
for i in $(seq 100 100 2000)
do
    echo -n "$i," 
    head "20news/20news.voc" -n $i > "temp/first$i.voc"
    ./run_with_vocabulary.sh "temp/first$i.voc"
    rm "temp/first$i.voc"
done
for i in $(seq 2000 1000 93000)
do
    echo -n "$i," 
    head "20news/20news.voc" -n $i > "temp/first$i.voc"
    ./run_with_vocabulary.sh "temp/first$i.voc"
    rm "temp/first$i.voc"
done
