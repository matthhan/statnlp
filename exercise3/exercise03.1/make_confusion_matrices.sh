#!/bin/bash
#smoothed
./program.out -r 20news/20news.tr -t 20news/20news.te -v 20news/20news.voc -s | tail -n +10 > confusion_matrix_smoothed.csv
#not smoothed
./program.out -r 20news/20news.tr -t 20news/20news.te -v 20news/20news.voc | tail -n +10 > confusion_matrix.csv
