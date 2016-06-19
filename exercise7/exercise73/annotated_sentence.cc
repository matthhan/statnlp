#include "annotated_sentence.hh"

AnnotatedSentence makeAnnotatedSentence(Sentence s,TagSequence tags) {
    auto result = AnnotatedSentence();
    for(int i = 0; i < s.size();i++) {
        result.push_back(make_tuple(s[i],tags[i]));
    }
    return result;
}
