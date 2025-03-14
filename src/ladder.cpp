#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error trying to find ladder from '" << word1 << "' to '" << word2 << "': " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.length() - (int)str2.length()) > d) {
        return false;
    }
    
    vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1, 0));
    
    for (size_t i = 0; i <= str1.length(); i++) {
        dp[i][0] = i;
    }
    for (size_t j = 0; j <= str2.length(); j++) {
        dp[0][j] = j;
    }
    
    for (size_t i = 1; i <= str1.length(); i++) {
        for (size_t j = 1; j <= str2.length(); j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
            }
            
            if (i == str1.length() && dp[i][j] <= d) {
                return true;
            }
        }
    }
    
    return dp[str1.length()][str2.length()] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) {
        return false;
    }
    
    int diff_count = 0;
    for (size_t i = 0; i < word1.length(); i++) {
        if (word1[i] != word2[i]) {
            diff_count++;
            if (diff_count > 1) {
                return false;
            }
        }
    }
    
    return diff_count == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word.length() != end_word.length()) {
        error(begin_word, end_word, "Words must be the same length");
    }
    
    set<string> all_words = word_list;
    all_words.insert(begin_word);
    all_words.insert(end_word);
    
    queue<vector<string>> paths;
    set<string> visited;
    
    paths.push({begin_word});
    visited.insert(begin_word);
    
    while (!paths.empty()) {
        vector<string> current_path = paths.front();
        paths.pop();
        
        string current_word = current_path.back();
        
        if (current_word == end_word) {
            return current_path;
        }
        
        for (const string& word : all_words) {
            if (visited.find(word) == visited.end() && is_adjacent(current_word, word)) {
                vector<string> new_path = current_path;
                new_path.push_back(word);
                paths.push(new_path);
                visited.insert(word);
            }
        }
    }
    
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open word list file: " << file_name << endl;
        exit(1);
    }
    
    string word;
    while (file >> word) {
        for (char& c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word Ladder (" << ladder.size() << " steps):" << endl;
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << (i + 1) << ". " << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " -> ";
        }
        if ((i + 1) % 5 == 0 && i != ladder.size() - 1) {
            cout << endl;
        }
    }
    cout << endl;
}

void verify_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder to verify." << endl;
        return;
    }
    
    bool valid = true;
    for (size_t i = 0; i < ladder.size() - 1; i++) {
        if (!is_adjacent(ladder[i], ladder[i + 1])) {
            cout << "Invalid transition from '" << ladder[i] << "' to '" << ladder[i + 1] << "'" << endl;
            valid = false;
        }
    }
    
    if (valid) {
        cout << "Word ladder is valid!" << endl;
    } else {
        cout << "Word ladder contains invalid transitions!" << endl;
    }
}
