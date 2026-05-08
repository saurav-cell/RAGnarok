#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <set>
#include <cmath>
#include<stdlib.h>

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
    for(auto p : tf){

    if(idf.find(p.first) != idf.end()){
        tfidf[p.first] = p.second * idf.at(p.first);
    }

}
    return tfidf;
}  

// cosine similarity
double cosineSimilarity(
    const map<string,double>& tfIDF_doc,
    const map<string,double>& queryTFIDF
){
    double dotProduct = 0.0;
    double docMagnitude = 0.0;
    double queryMagnitude = 0.0;

    // Dot Product + Query Magnitude
    for(auto p : queryTFIDF){

        if(tfIDF_doc.find(p.first) != tfIDF_doc.end()){
            dotProduct += p.second * tfIDF_doc.at(p.first);
        }

        queryMagnitude += p.second * p.second;
    }

    // Document Magnitude
    for(auto p : tfIDF_doc){
        docMagnitude += p.second * p.second;
    }

    // Avoid division by zero
    if(docMagnitude == 0 || queryMagnitude == 0){
        return 0.0;
    }

    return dotProduct / (sqrt(docMagnitude) * sqrt(queryMagnitude));
}
int main() {
    string line;
    vector<string> rawDocuments;
    vector<vector<string>> documents;

    ifstream file("../data/docs.txt");

    if (!file) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // Preprocessing pipeline
   while (getline(file, line)) {

    rawDocuments.push_back(line);

    string processed = preprocess(line);

    vector<string> words = splitWords(processed);

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
   /*for (int i = 0; i < tf_docs.size(); i++) {
    cout << "Document " << i << ":\n";

    for (auto p : tf_docs[i]) {
        cout << p.first << " : " << p.second << endl;
    }

    cout << endl;
 }*/

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

//query processing
string query;
cout << "Enter query: ";
getline(cin, query);
query = preprocess(query);
vector<string> queryWords = splitWords(query);
queryWords = filtered(queryWords);
map<string,int> queryTF = buildTF(queryWords);
map<string,double> queryTFIDF = buildTFIDF(idf, queryTF);


//cout << "\nQuery TF-IDF:\n";

/*for(auto p : queryTFIDF){
    cout << p.first << " : " << p.second << endl;
}*/

// Retrieval
double bestScore = -1.0;
int bestDocIndex = -1;

for(int i = 0; i < tfidf_docs.size(); i++){

    double score = cosineSimilarity(tfidf_docs[i], queryTFIDF);

    //cout << "Document " << i << " Similarity: " << score << endl;

    if(score > bestScore){
        bestScore = score;
        bestDocIndex = i;
    }
}

//cout << "\nBest Matching Document: " << bestDocIndex << endl;

//cout << "Best Similarity Score: " << bestScore << endl;
//cout << "\nRetrieved Context:\n";
//cout << rawDocuments[bestDocIndex] << endl;

//prompt construction
string prompt =
    "Use the following context to answer the question.\n"
    "If the answer is not in the context, say you don't know.\n\n"
    "Context:\n" +
    rawDocuments[bestDocIndex] +
    "\n\nQuestion:\n" +
    query +
    "\n\nAnswer:\n";


    cout << "\nGenerated Prompt:\n";
    cout << prompt << endl;
    ofstream promptFile("prompt.txt");

    promptFile << prompt;

    promptFile.close();

    // Call LLM
    string command =
    "cmd /c \"\"C:\\Users\\User_PC\\llama.cpp\\build\\bin\\llama-cli.exe\" "
    "-m \"C:\\Users\\User_PC\\Downloads\\tinyllama-1.1b-chat-v1.0.Q4_K_M.gguf\" "
    "-f \"prompt.txt\"\"";

    cout << "\nRunning TinyLlama...\n";

    cout << "\nCommand:\n" << command << endl;
    system(command.c_str());

    return 0;
}