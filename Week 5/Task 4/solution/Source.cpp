#include "test_runner.h"

#include <vector>
#include <utility>

template <typename Token>
using Sentence = std::vector<Token>;

template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens)
{
    Sentence<Token> tmp;
    std::vector<Sentence<Token>> result;
    result.reserve(tokens.size());

    for (auto it = tokens.begin(); it != tokens.end(); it++)
    {
        if (it == std::prev(tokens.end()) || (it->IsEndSentencePunctuation() && !std::next(it)->IsEndSentencePunctuation()))
        {
            tmp.push_back(std::move(*it));
            result.push_back(std::move(tmp));
        }
        else
        {
            tmp.push_back(std::move(*it));
        }

    }

    if (result.empty() || result.back() != tmp)
    {
        if (!tmp.empty())
        {
            result.push_back(std::move(tmp));
        }
    }

    result.shrink_to_fit();

    return result;
}


struct TestToken
{
    std::string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

std::ostream& operator<<(std::ostream& stream, const TestToken& token)
{
    return stream << token.data;
}

void TestSplitting()
{
    ASSERT_EQUAL(
        SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
        std::vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!"}}
            })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
        std::vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
            })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
        std::vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
            {{"Without"}, {"copies"}, {".", true}},
            })
            );
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
}