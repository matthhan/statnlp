#ifndef ANNOTATED_SENTENCE_HH
#define ANNOTATED_SENTENCE_HH
#include "tag_sequence.hh"
#include "sentence.hh"
#include <vector>
#include <utility>

using std::vector;
using std::make_tuple;
using std::pair;
typedef vector<pair<Word,Pos>>  AnnotatedSentence;
AnnotatedSentence makeAnnotatedSentence(Sentence s,TagSequence tags);
#endif
