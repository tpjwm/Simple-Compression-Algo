#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <regex>


std::map<std::string, unsigned short> findMostCommonWords(std::string &text){
    std::map<std::string, unsigned short> mostCommonWords;
    std::vector<std::string> tokens;

    //split string and tokenize based on spaces
    std::istringstream iss(text);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(tokens));

    for (const std::string& c : tokens) {
        if(mostCommonWords.find(c) == mostCommonWords.end()){
            mostCommonWords.insert(std::pair<std::string, unsigned short>(c, 1));
        }
        else{
            mostCommonWords.at(c)++;
        }
    }
    return mostCommonWords;
}

/**
 * Compresses text and returns compressed text. Compresses by finding duplicate words and replacing with single character
 * placeholders. Limited currently to 65535 duplicates / characters.
 * @param originalText is the original text without compression
 * @param commonWords vector of duplicates sorted by most common to least common
 * @return
 */
std::string getCompressedText(const std::string &originalText, const std::vector<std::string>  &commonWords, bool useSmallCompress){
    std::string compressedText = originalText;
    size_t counter = -128;
    for(const auto & word: commonWords){
        compressedText = std::regex_replace(compressedText, std::regex(word), std::string{static_cast<char>(counter)}); // replace 'word.first' -> '1'
        counter++;
    }
    return compressedText;
}

/**
 * Reverses compression and replaces symbols with the original words.
 * @param compressedText is the compressed text containing symbols / characters
 * @param commonWords vector of duplicates sorted by most common to least common
 * @return
 */
std::string getUncompressedText(const std::string &compressedText, const std::vector<std::string> &commonWords, bool useSmallCompress){
    std::string uncompressedText = compressedText;
    if (useSmallCompress){
        size_t counter = -128;
        for(const auto & word: commonWords){
            uncompressedText = std::regex_replace(uncompressedText, std::regex(std::string{static_cast<char>(counter)}), word); // replace '1' -> 'word.first'
            counter++;
        }
    }
    else{
        size_t counter = 0;
        for(const auto & word: commonWords){
            unsigned short value = counter;
            uncompressedText = std::regex_replace(uncompressedText, std::regex(std::to_string(value)), word); // replace '1' -> 'word.first'
            counter++;
        }
    }

    return uncompressedText;
}
int main() {
    std::string text = "In a man-cave there lived a brilliant, sly man named Detective Jenkins. Not a lonely depressed, scary man-cave, filled with riches and a foul smell, nor yet a cold, bare, productive man-cave with nothing in it to sit down on or to eat on. It was a manly man-cave, and that means procrastination. One day, after a troubling visit from the accountant Giga Watson, Detective Jenkins leaves his man-cave and sets out in search of three golden fedoras. A quest undertaken in the company of a businessman, a dog and a tall woman. In the search for the feminist-guarded fedoras, Detective Jenkins surprises even himself with his agility and skill as a dog food taster. During his travels, Jenkins rescues a goblet, an heirloom belonging to Giga Watson. But when Giga Watson refuses to try opium, their friendship is over. However, Giga Watson is badly injured at the Great Battle of '99 and the two reconcile just before Detective Jenkins engages in some serious opium smoking. Detective Jenkins accepts one of the three golden fedoras and returns to his cave a very wealthy and changed man.";
    std::cout << "Original string size: " << text.size() << " bytes" << std::endl;
    std::cout << "Original string: " << text << std::endl;

    std::map<std::string, unsigned short> mostCommonWords = findMostCommonWords(text);

    std::vector<std::string> duplicatesVector;
    for(const auto & mostCommonWord : mostCommonWords)
    {
        if(mostCommonWord.second >= 2) //only stores data for duplicates
            duplicatesVector.emplace_back(mostCommonWord.first);
    }

    std::string compressed;
    bool useSmallCompress = true;
    if(duplicatesVector.size() <= 160){
        //use chars as symbol (with 128 negative values, 32 positive)
        compressed = getCompressedText(text, duplicatesVector, useSmallCompress);
    }
    else if(duplicatesVector.size() <= 0xffff){
        //use unsigned shorts as symbol (aka 2 bytes per symbol)
        useSmallCompress = false;
        compressed = getCompressedText(text, duplicatesVector , useSmallCompress);
    }
    else{
        //send only top 0xffff duplicates
        ///TODO: Sort duplicate vector in order of most bytes used to prioritize compressing larger strings
        useSmallCompress = false;

        auto firstIterator = duplicatesVector.begin();
        auto secondIterator = duplicatesVector.begin() + 0xffff;
        std::vector<std::string> slicedVec(firstIterator, secondIterator);

        compressed = getCompressedText(text, slicedVec, useSmallCompress);
    }

    std::cout << "String size compressed: " << compressed.size() << " bytes" << std::endl;
    std::cout << "String compressed: " << compressed << std::endl;

    std::string uncompressed = getUncompressedText(compressed, duplicatesVector, useSmallCompress);
    std::cout << "String size uncompressed: " << uncompressed.size() << " bytes" << std::endl;
    std::cout << "String uncompressed: " << uncompressed << std::endl;

    return 0;
}
