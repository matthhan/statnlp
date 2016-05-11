#!/bin/bash

echo "vocabulary_size,classifier_accuracy,rejections"
for i in $(seq 100 100 2000)
do
    echo -n "$i," 
    head -n $i 20news/20news.voc  > "temp/first$i.voc"
    ./run_with_vocabulary_smoothed.sh "temp/first$i.voc"
    rm "temp/first$i.voc"
done
for i in $(seq 2000 1000 93000)
do
    echo -n "$i," 
    head -n $i 20news/20news.voc  > "temp/first$i.voc"
    ./run_with_vocabulary_smoothed.sh "temp/first$i.voc"
    rm "temp/first$i.voc"
done
