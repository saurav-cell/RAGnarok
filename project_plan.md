RAG C++ — Project Plan
Phase 1: Retrieval (core logic)
1. Load documents
  → read file into vector<string>
2. Preprocess
   → lowercase
   → remove punctuation
   → split into words
   → remove stopwords
   → result: vector<vector<string>>
3. Term Frequency (TF)
   → count words in each document
   → map<string, int>
4. Document Frequency (DF)
   → count in how many docs each word appears
5. Inverse Document Frequency (IDF)
   → idf = log(total_docs / df)
6. TF-IDF
   → weight each word (TF × IDF)
   → map<string, double>
7. Query
   → apply same preprocessing
   → convert to TF-IDF vector
8. Similarity 
   → compare query with each doc (cosine similarity)
9. Retrieval
   → return document with highest score
Phase 2: Generation (llama.cpp)
1. Load model
   → use llama.cpp with GGUF model
2. Prepare prompt
   → combine retrieved document + user query
   → format clearly:
   Context: <text>
   Question: <query>
   Answer:
3. Run model
   → send prompt to llama.cpp
   → set parameters (max tokens, temperature)
4. Get output
   → receive generated answer
   → print in CLI

//Rules
* Follow order strictly
* No extra libraries
* Keep code simple and understandable
