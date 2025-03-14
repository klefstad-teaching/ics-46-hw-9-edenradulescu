#include "ladder.h"

int main() {
    set<string> word_list;
    
    load_words(word_list, "wordlist.txt");
    
    string begin_word, end_word;
    cout << "Enter starting word: ";
    cin >> begin_word;
    cout << "Enter ending word: ";
    cin >> end_word;
    
    for (char& c : begin_word) c = tolower(c);
    for (char& c : end_word) c = tolower(c);
    
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
    
    verify_word_ladder(ladder);
    
    return 0;
}