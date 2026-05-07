#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <set>
#include <cmath>

using namespace std;

// Preprocess (lowercase + remove punctuation)
string preprocess(string text) {
    string cleaned = "";

    for (int i = 0; i < text.size(); i++) {
        char c = tolower(text[i]);

        if ((c >= 'a' && c <= 'z') || c == ' ') {
            cleaned += c;
        }
    }

    return cleaned;
}

// Split words
vector<string> splitWords(string text) {
    vector<string> words;
    string current = "";

    for (int i = 0; i < text.size(); i++) {
        if (text[i] != ' ') {
            current += text[i];
        } else {
            if (!current.empty()) {
                words.push_back(current);
                current = "";
            }
        }
    }

    if (!current.empty()) {
        words.push_back(current);
    }

    return words;
}

// Stopwords removal
vector<string> filtered(const vector<string>& words) {
    vector<string> stopwords = {
        "a","an","the","and","is","in","on","at","for","to","from",
        "of","with","by","this","that","it","as","be","are","was","were",
        "has","have","had","do","does","did","but","not","or","can"
    };

    vector<string> filteredWords;

    for (int i = 0; i < words.size(); i++) {
        bool isStopWord = false;

        for (int j = 0; j < stopwords.size(); j++) {
            if (words[i] == stopwords[j]) {
                isStopWord = true;
                break;
            }
        }

        if (!isStopWord) {
            filteredWords.push_back(words[i]);
        }
    }

    return filteredWords;
}

// TF function
map<string, int> buildTF(const vector<string>& words) {
    map<string, int> freq;

    for (int i = 0; i < words.size(); i++) {
        freq[words[i]]++;
    }

    return freq;
}

//DF function
map<string, int> buildDF(const vector<vector<string>>& documents){
    map<string, int> df;

    for (int i = 0; i < documents.size(); i++) {
        set<string> uniqueWords;

        for (int j = 0; j < documents[i].size(); j++) {
            uniqueWords.insert(documents[i][j]);
        }

        for (const string& word : uniqueWords) {
            df[word]++;
        }
    }

    return df;
}

//IDF function
map<string,double> buildIDF(const map<string,int>& df, int totalDocs){
    map<string,double> idf;
    for(auto p: df){
        idf[p.first] = log((double)totalDocs /  p.second);
    }
    return idf;
}

//TF-IDF function
map<string,double> buildTFIDF( const map<string,double>& idf,const map<string,int>& tf){
    map<string,double> tfidf;
    for(auto p: tf){
        tfidf[p.first] = p.second * idf.at(p.first);
    }
    return tfidf;
}  
int main() {
    string line;
    vector<vector<string>> documents;

    ifstream file("../data/docs.txt");

    if (!file) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // Preprocessing pipeline
    while (getline(file, line)) {
        line = preprocess(line);
        vector<string> words = splitWords(line);
        words = filtered(words);
        documents.push_back(words);
    }

    file.close();

    // Build TF for all documents
    vector<map<string, int>> tf_docs;

    for (int i = 0; i < documents.size(); i++) {
        tf_docs.push_back(buildTF(documents[i]));
    }

    // Print TF of first document
   for (int i = 0; i < tf_docs.size(); i++) {
    cout << "Document " << i << ":\n";

    for (auto p : tf_docs[i]) {
        cout << p.first << " : " << p.second << endl;
    }

    cout << endl;
 }

 //DF
 map<string, int> df = buildDF(documents);

 /*cout << "\nDocument Frequency:\n";

for (auto p : df) {
    cout << p.first << " : " << p.second << endl;
}*/

//idf
map<string,double> idf = buildIDF(df, documents.size());
/*cout << "\nIDF Values:\n";

for(auto p : idf){
    cout << p.first << " : " << p.second << endl;
}
*/

//TF-IDF
vector<map<string,double>> tfidf_docs;
for(int i = 0; i < tf_docs.size(); i++){
    tfidf_docs.push_back(buildTFIDF( idf,tf_docs[i]));
}

/*cout << "\nTF-IDF Values:\n";

for(int i = 0; i < tfidf_docs.size(); i++){
    cout << "Document " << i << ":\n";

    for(auto p : tfidf_docs[i]){
        cout << p.first << " : " << p.second << endl;
    }

    cout << endl;
}*/

    return 0;
}