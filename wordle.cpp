#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


void gen_map(const std::string& str, std::map<char, int>& str_map);


void gen_words(
    const std::string& in,
    const std::string& floating,
    size_t floating_iter,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    std::string& current,
    size_t length,
    size_t empty_index
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    
    std::string current(in);
    
    size_t cnt = 0;
    for (auto c: in) {
        if (c != '-') {
            cnt++;
        }
    }

    gen_words(in, floating, 0, dict, result, current, cnt, 0);
    return result;
}

// Define any helper functions here

void gen_words(
    const std::string& in,
    const std::string& floating,
    size_t floating_iter,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    std::string& current,
    size_t length,
    size_t empty_index
) {
    if (length >= in.length()) {
        if (dict.find(current) != dict.end()) {
            result.insert(current);
        }
        return;
    }

    if (floating_iter < floating.length()) {
        for (size_t i = 0; i < in.length(); i++) {
            if (current[i] == '-') {
                current[i] = floating[floating_iter];
                gen_words(in, floating, floating_iter + 1, dict, result, current, length + 1, empty_index);
                current[i] = '-';
            }
        }
    } else {
        while (current[empty_index] != '-') {
            empty_index++;
        }
        for (char ch = 'a'; ch <= 'z'; ch++) {
            current[empty_index] = ch;
            gen_words(in, floating, floating_iter, dict, result, current, length + 1, empty_index);
            current[empty_index] = '-';
        }
    }
}
