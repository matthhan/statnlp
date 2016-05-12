-----------------HOW TO RUN--------------------------------
- Run 'make' to compile everything.
- The final program will be stored as ./program.out. 
  Run this to get an overview of the command line arguments that can be passed.
- To try running the classifier once with the full vocabulary, you can run 'run.sh'.
- The results obtained by running the classifier with different vocabulary sizes are stored as
  result.csv and result_smoothed.csv. They can be generated with the script 'test_partial_vocabularies.sh'.
  You may not want to run the script yourself, because it takes a lot of time 
  and it makes temporary files for the smaller vocabularies.
- The plots for these results are 'accuracy_naive.png' and 'accuracy_smoothed.png'. 
  They were generated with the R programming language and the 'ggplot2' and 'reshape2' packages.
  If you want to generate them yourself, install the R 
  language and run "install.packages(c("ggplot2","reshape"))". 
  Then run the script contained in 'plot_script.R'.
- Confusion Matrices can be found in confusion_matrix.csv and confusion_matrix_smoothed.csv. 
  They can be generated with the script 'make_confusion_matrices.sh'
- Finally, the classifier can be run on the spam corpus with the script 'run_spam.sh'.
-----------------OVERVIEW OF PROGRAM----------------------------------
To implement the multinomial classifier, we made the choice of using
Log probabilities instead of normal probabilities, so that we do not
have any problems with floating point precision. Note that this does
not invalidate the classification, as it is mathematically the same
thing.

In part b of the exercise, we were asked to devise a smoothing method
for class conditional word probabilities.
To achieve this, words with a frequency of 0 in the vocabulary 
are assigned a frequency of 1 instead. The normalization Factor
for probability calculation is changed accordingly to make
sure that probabilities still add up to 1.

Our program reuses the Dictionary class from a previous exercise. 

In addition, a Document class was written to parse each line in the
data files into a more useful representation. Specifically, a 
Document is represented as a map from word indexes in the dictionary
to counts. Unknown words are assigned an index of -1. 
The true class of a document is also stored in this class.

The classifier itself is represented by the class MultinomialClassifier.
Training is done by the method 'trainOnDocument' and consists of 
passing the document on to the class frequency model and the
multinomial model that keeps track of class conditional word frequencies.
Classifying is done in a method 'classify' by calculating the 
Log probabilities of each class given the document. Then the class
with the highest Log probability is chosen, unless each class has a
Log probability of -inf, in which case the special class "REJECT" is chosen.

To keep track of the models, there are classes ClassCounter and 
MultinomialModel, which keep track of class frequencies and class conditional
word frequencies respectively.

Finally, we wrote a class ConfusionMatrix, which keeps track of the results
of classification and can display it in a nice form.
