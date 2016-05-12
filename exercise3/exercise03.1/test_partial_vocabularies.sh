#!/bin/bash
mkdir temp;
#unsmoothed
(echo "vocabulary_size,classifier_accuracy,rejections"
#High resolution for small vocabulary sizes
for i in $(seq 100 100 2000)
do
    echo -n "$i," 
    head -n $i 20news/20news.voc  > "temp/first$i.voc"
    ./program.out -r 20news/20news.tr -t 20news/20news.te -v "temp/first$i.voc" -q -p
    rm "temp/first$i.voc"
done
#Lower resolution for big vocabulary sizes
for i in $(seq 2000 1000 93000)
do
    echo -n "$i," 
    head -n $i 20news/20news.voc  > "temp/first$i.voc"
    ./program.out -r 20news/20news.tr -t 20news/20news.te -v "temp/first$i.voc" -q -p
    rm "temp/first$i.voc"
done) > result.csv

#Same but smoothed
(echo "vocabulary_size,classifier_accuracy,rejections"
#High resolution for small vocabulary sizes
for i in $(seq 100 100 2000)
do
    echo -n "$i," 
    head -n $i 20news/20news.voc  > "temp/first$i.voc"
    ./program.out -r 20news/20news.tr -t 20news/20news.te -v "temp/first$i.voc" -q -p -s
    rm "temp/first$i.voc"
done
#Lower resolution for big vocabulary sizes
for i in $(seq 2000 1000 93000)
do
    echo -n "$i," 
    head -n $i 20news/20news.voc  > "temp/first$i.voc"
    ./program.out -r 20news/20news.tr -t 20news/20news.te -v "temp/first$i.voc" -q -p -s
    rm "temp/first$i.voc"
done) > result_smoothed.csv
