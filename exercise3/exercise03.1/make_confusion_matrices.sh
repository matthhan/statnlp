#!/bin/bash
#not smoothed
./program.out -r 20news/20news.tr -t 20news/20news.te -v 20news/20news.voc -q -c > confusion_matrix.csv
#smoothed
./program.out -r 20news/20news.tr -t 20news/20news.te -v 20news/20news.voc -s -q -c > confusion_matrix_smoothed.csv
