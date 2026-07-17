#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <set>
#include <cmath>
#include<stdlib.h>
#include <algorithm>
#include <chrono>
#include "../include/preprocessing.h"
using namespace std;







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
// Sanitize prompt for CMD: remove newlines, escape double quotes
string sanitizeForCmd(const string& text) {
    string result = "";
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        if (c == '\n' || c == '\r') {
            result += ' ';          // flatten newlines to spaces
        } else if (c == '"') {
            result += "\\\"";       // escape double quotes
        } else if (c == '\\') {
            result += "\\\\";       // escape backslashes
        } else {
            result += c;
        }
    }
    return result;
}
int main() {
    string line;
    vector<string> rawDocuments;
    vector<vector<string>> documents;

    ifstream file("data/docs.txt");

    if (!file) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // Preprocessing pipeline
  string chunk = "";

while(getline(file, line)){

    // Empty line means new paragraph
    if(line.empty()){

        if(!chunk.empty()){

            rawDocuments.push_back(chunk);

            string processed = preprocess(chunk);

            vector<string> words = splitWords(processed);

            words = filtered(words);

            documents.push_back(words);

            chunk = "";
        }

        continue;
    }

    chunk += line + " ";
    if(chunk.size() > 500){

    rawDocuments.push_back(chunk);

    string processed = preprocess(chunk);

    vector<string> words = splitWords(processed);

    words = filtered(words);

    documents.push_back(words);

    chunk = "";
}
}

// Last chunk
if(!chunk.empty()){

    rawDocuments.push_back(chunk);

    string processed = preprocess(chunk);

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
cout << "====================================================\n";
cout << "                 RAGnarok v1.0\n";
cout << "        Lightweight Offline RAG System\n";
cout << "====================================================\n\n";

cout << "Language Model : TinyLlama 1.1B (GGUF)\n";
cout << "Retriever      : TF-IDF + Cosine Similarity\n";
cout << "Execution Mode : Local CPU\n";
cout << "Documents      : " << rawDocuments.size() << "\n";
cout << "Chunk Size     : 500 characters\n";

cout << "\n====================================================\n";
//query processing
while(true){
   
    string query;
   cout << "\nAsk your question (/exit to quit): ";
    getline(cin, query);
    if(query == "/exit"){
        break;
    }
    query = preprocess(query);
    vector<string> queryWords = splitWords(query);
queryWords = filtered(queryWords);
map<string,int> queryTF = buildTF(queryWords);
map<string,double> queryTFIDF = buildTFIDF(idf, queryTF);


//cout << "\nQuery TF-IDF:\n";

/*for(auto p : queryTFIDF){
    cout << p.first << " : " << p.second << endl;
}*/
auto retrievalStart = chrono::high_resolution_clock::now();
// Retrieval
vector<pair<double,int>> scores;

// Calculate similarity scores
for(int i = 0; i < tfidf_docs.size(); i++){

    double score = cosineSimilarity(tfidf_docs[i], queryTFIDF);

    if(score > 0.15){ // Threshold for relevance
        scores.push_back({score, i});
    }
}

// No match found
if(scores.empty()){
    cout << "No relevant context found.\n";
    continue;
}

// Sort highest score first
sort(scores.rbegin(), scores.rend());

cout << "\n========================================\n";
cout << "          Top Retrieved Chunks\n";
cout << "========================================\n\n";

// Build final context
string finalContext = "";

for(int i = 0; i < 3 && i < scores.size(); i++){

    int idx = scores[i].second;

    cout << "Source : OOPs_CPP_Academic_Notes.pdf" << endl;

    cout << "Chunk "
         << idx
         << " | Score: "
         << scores[i].first
         << endl << endl;

    finalContext += rawDocuments[idx] + "\n";
}
//cout << "\nRetrieved Context:\n";
//cout << rawDocuments[bestDocIndex] << endl;
auto retrievalEnd = chrono::high_resolution_clock::now();

auto retrievalTime =
    chrono::duration_cast<chrono::milliseconds>(
        retrievalEnd - retrievalStart
    );
// Prompt construction
string prompt =
    "You are a question answering assistant. "
    "Answer ONLY using the given context. "
    "If the answer is not present, say: Not found in document. "
    "Keep answer short and clear. "
    "Context: " + finalContext +
    " Question: " + query +
    " Answer:";

// Write sanitized prompt to file (for debugging if needed)
ofstream promptFile("data/prompt.txt");
promptFile << prompt;
promptFile.close();

// Sanitize for CMD embedding
string safePrompt = sanitizeForCmd(prompt);

// Command:
// - No -f flag (avoids interactive mode in old builds)
// - -p with sanitized single-line prompt
// - -n 128: generate exactly 128 tokens then exit
// - < NUL: redirects stdin from null device so llama-cli
//          gets EOF immediately and cannot enter interactive mode
string command =
    "cd /d C:\\Users\\User_PC\\llama.cpp\\build\\bin && "
    "llama-cli.exe "
    "-m \"C:\\Users\\User_PC\\Downloads\\tinyllama-1.1b-chat-v1.0.Q4_K_M.gguf\" "
    "-f \"C:\\Users\\User_PC\\OneDrive\\Desktop\\RAGNAROK\\data\\prompt.txt\"";


    cout << "\nRetrieval Time: "
     << retrievalTime.count()
     << " ms\n";
cout << "\nRunning TinyLlama...\n";
//ofstream outFile("data/prompt.txt");
//outFile << prompt;
//outFile.close();

cout << "\nGenerating answer...\n\n";

system(command.c_str());






cout << "Retrieval Time : "
     << retrievalTime.count()
     << " ms\n";


}
    return 0;
}