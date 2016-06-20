#include "annotated_sentence.hh"

AnnotatedSentence makeAnnotatedSentence(Sentence s,TagSequence tags) {
    auto result = AnnotatedSentence();
    for(unsigned int i = 0; i < s.size();i++) {
        result.push_back(make_pair(s[i],tags[i]));
    }
    return result;
}
