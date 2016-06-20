This is our implementation of the POS tagger. We have extensively reused code from previous exercises, such as the Dictionary class, as well as the code to parse a language model from the SRI toolkit and the basic skeleton for the main method (including e.g. the code that handles command line arguments).

To do POS-tagging, we use a membership model and a pos bigram model. We train the membership model ourselves, using a simple smoothing method that we used before for the document classifier, while the pos bigram model is trained using the SRI toolkit and smoothed with the Kneser-Ney method. Finally, the dynamic programming is carried out in the PosTagger class. Testing this on the provided training data set, we reached an error rate of roughly 10%. A ``greedy'' method without dynamic programming that we also implemented achieved an error rate of roughly 12%. It can be selected by passing the command line argument -g.

Steps to execute
1. Execute the Makefile
2. Create the language model with the script "make_language_model.sh". The SRI toolkit needs to be installed for this step.
3. Run the finished program "program.out". To do so, you can e.g. use the provided script "run.sh".
