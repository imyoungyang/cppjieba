#include <iostream>
#include <ctime>
#include <fstream>
#include "../src/Limonp/ArgvContext.hpp"
#include "../src/Limonp/io_functs.hpp"
#include "../src/MPSegment.hpp"
#include "../src/HMMSegment.hpp"
#include "../src/MixSegment.hpp"
#include "../src/KeywordExtractor.hpp"

using namespace CppJieba;

void cut(size_t times = 20)
{
    MixSegment seg("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8");
    assert(seg);
    vector<string> res;
    string doc;
    loadFile2Str("../test/testdata/weicheng.utf8", doc);
    long beginTime = clock();
    for(size_t i = 0; i < times; i ++)
    {
        printf("process [%3.0lf %%]\r", 100.0*(i+1)/times);
        fflush(stdout);
        res.clear();
        seg.cut(doc, res);
    }
    long endTime = clock();
    printf("\ncut: [%.3lf seconds]time consumed.\n", double(endTime - beginTime)/CLOCKS_PER_SEC);
}

void extract(size_t times = 400)
{
    KeywordExtractor extractor("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8", "../dict/stop_words.utf8");
    assert(extractor);
    vector<string> words;
    string doc;
    loadFile2Str("../test/testdata/review.100", doc);
    long beginTime = clock();
    for(size_t i = 0; i < times; i ++)
    {
        printf("process [%3.0lf %%]\r", 100.0*(i+1)/times);
        fflush(stdout);
        words.clear();
        extractor.extract(doc, words, 5);
    }
    long endTime = clock();
    printf("\nextract: [%.3lf seconds]time consumed.\n", double(endTime - beginTime)/CLOCKS_PER_SEC);
}

int main(int argc, char ** argv)
{
    cut();
    extract();
    return EXIT_SUCCESS;
}
