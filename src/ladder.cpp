#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error: trying to find ladder from '" << word1 << "' to '" << word2 << "': " << msg << endl;
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
    if (word1 == word2) {
        return true;
    }
    
    int len_diff = abs((int)word1.length() - (int)word2.length());
    if (len_diff > 1) {
        return false;
    }
    
    if (word1.length() == word2.length()) {
        int diff_count = 0;
        for (size_t i = 0; i < word1.length(); i++) {
            if (word1[i] != word2[i]) {
                diff_count++;
                if (diff_count > 1) {
                    return false;
                }
            }
        }
        return diff_count <= 1; 
    }
    
    const string& shorter = (word1.length() < word2.length()) ? word1 : word2;
    const string& longer = (word1.length() < word2.length()) ? word2 : word1;
    
    size_t s_idx = 0, l_idx = 0;
    bool found_diff = false;
    
    while (s_idx < shorter.length() && l_idx < longer.length()) {
        if (shorter[s_idx] != longer[l_idx]) {
            if (found_diff) {
                return false; 
            }
            found_diff = true;
            l_idx++; 
        } else {
            s_idx++;
            l_idx++;
        }
    }
    
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
   queue<vector<string>> ladder_queue;
   set<string> visited;
   ladder_queue.push({begin_word});
   visited.insert(begin_word);
   while (!ladder_queue.empty()) {
       vector<string> ladder = ladder_queue.front();
       ladder_queue.pop();
       string last_word = ladder.back();
       for (const string& word : word_list) {
           if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
               vector<string> new_ladder = ladder;
               new_ladder.push_back(word);
               visited.insert(word);
               if (word == end_word) return new_ladder;
               ladder_queue.push(new_ladder);
           }
       }
   }
   return {};
}

void load_words(set<string> & word_list, const string& file_name) {
   ifstream file(file_name);
   if (!file) {
       cerr << "Error: Unable to open file " << file_name << endl;
       return;
   }
   string word;
   while (file >> word) {
       word_list.insert(word);
   }
   file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
}

void verify_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "Empty ladder is valid" << endl;
        return;
    }
    
    bool valid = true;
    for (size_t i = 0; i < ladder.size() - 1; i++) {
        if (!is_adjacent(ladder[i], ladder[i + 1])) {
            cout << "Invalid transition from '" << ladder[i] << "' to '" << ladder[i + 1] << "'" << endl;
            valid = false;
            break;  
        }
    }
    
    if (valid) {
        cout << "Word ladder is valid!" << endl;
    } else {
        cout << "Word ladder contains invalid transitions!" << endl;
    }
}