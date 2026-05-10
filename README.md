# Lightweight Local RAG System in C++ using llama.cpp

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![llama.cpp](https://img.shields.io/badge/llama.cpp-Local%20LLM-green)
![TinyLlama](https://img.shields.io/badge/Model-TinyLlama-orange)
![CPU Only](https://img.shields.io/badge/Execution-CPU%20Only-red)
![Status](https://img.shields.io/badge/Status-Working-success)

A lightweight Retrieval-Augmented Generation (RAG) pipeline implemented completely from scratch in pure C++ using llama.cpp and TinyLlama.

</div>

---

# Table of Contents

1. Introduction
2. Problem Statement
3. Objectives
4. What is RAG?
5. System Architecture
6. Core Pipeline
7. Features
8. Technical Stack
9. Why This Project?
10. Project Workflow
11. Detailed Implementation
12. Retrieval Pipeline
13. Hallucination Reduction
14. Model Integration
15. Folder Structure
16. Installation & Setup
17. Execution Flow
18. Example Queries
19. Sample Outputs
20. Challenges Faced
21. Performance Considerations
22. Current Limitations
23. Future Scope
24. Learning Outcomes
25. Authors
26. Acknowledgements
27. License

---

# Introduction

Retrieval-Augmented Generation (RAG) is one of the most important modern AI system architectures. Instead of relying entirely on the internal knowledge of a Large Language Model (LLM), a RAG system first retrieves relevant external information and then generates answers using that retrieved context.

This project demonstrates a complete lightweight implementation of the RAG concept using:

* pure C++
* llama.cpp
* TinyLlama
* TF-IDF retrieval
* cosine similarity
* local CPU-based inference

The entire system is designed to be:

* lightweight
* explainable
* beginner-friendly
* locally executable
* independent of cloud APIs

Unlike many high-level AI applications that depend heavily on frameworks, this project focuses on understanding the internal mechanics of retrieval systems and local LLM integration.

---

# Problem Statement

Traditional Large Language Models often suffer from:

* hallucination
* outdated knowledge
* inability to access custom user documents
* lack of controllability

When asked questions outside their reliable knowledge range, LLMs may generate highly confident but incorrect answers.

The goal of this project is to reduce this problem by grounding the language model using retrieved document context.

---

# Objectives

The primary objectives of this project are:

* Build a Retrieval-Augmented Generation system completely in C++
* Understand retrieval systems from scratch
* Integrate a local LLM using llama.cpp
* Run inference entirely on CPU
* Support lightweight hardware (8GB RAM)
* Implement hallucination reduction using retrieval filtering
* Avoid high-level frameworks and hidden abstractions

---

# What is RAG?

Retrieval-Augmented Generation combines two major components:

## 1. Retrieval System

Responsible for:

* searching documents
* finding relevant information
* ranking relevant chunks

## 2. Language Model

Responsible for:

* understanding the retrieved context
* generating final natural language answers

Instead of asking the language model directly:

```text
Question → LLM → Answer
```

RAG introduces an intermediate retrieval step:

```text
Question
   ↓
Retrieve Relevant Context
   ↓
Context + Question
   ↓
LLM
   ↓
Grounded Answer
```

This significantly improves reliability and reduces hallucination.

---

# System Architecture

## Overview

This project is a lightweight Retrieval-Augmented Generation (RAG) system implemented completely in **pure C++** using **llama.cpp** and **TinyLlama**.

The primary goal of this project is to understand and implement the **core RAG pipeline from scratch** without relying on high-level AI frameworks such as LangChain or cloud-based APIs.

The system runs entirely on:

* CPU only
* 8GB RAM compatible hardware
* local documents
* local LLM inference

This project demonstrates how modern retrieval-based AI systems work internally while remaining lightweight, explainable, and beginner-friendly.

---

# Features

* Local Retrieval-Augmented Generation (RAG)
* Pure C++ implementation
* TF-IDF based document vectorization
* Cosine similarity retrieval
* Document chunking pipeline
* Top-K relevant chunk retrieval
* TinyLlama integration using llama.cpp
* Hallucination reduction using similarity threshold filtering
* CPU-only execution
* Lightweight architecture suitable for low-resource systems
* Interactive CLI interface

---

# RAG Pipeline Architecture

```text
User Query
    ↓
Text Preprocessing
    ↓
TF-IDF Vectorization
    ↓
Cosine Similarity Search
    ↓
Top Relevant Chunk Retrieval
    ↓
Prompt Construction
    ↓
TinyLlama (llama.cpp)
    ↓
Generated Answer
```

---

# Project Motivation

Traditional Large Language Models can hallucinate or generate information unrelated to a user’s documents.

Retrieval-Augmented Generation solves this by:

1. Retrieving relevant information from external documents
2. Passing that information to the language model as context
3. Generating grounded answers based on retrieved content

This project focuses on implementing this mechanism manually to deeply understand how RAG systems operate internally.

---

# Tech Stack

| Component            | Technology          |
| -------------------- | ------------------- |
| Programming Language | C++                 |
| LLM Runtime          | llama.cpp           |
| Language Model       | TinyLlama 1.1B Chat |
| Retrieval Method     | TF-IDF              |
| Similarity Metric    | Cosine Similarity   |
| Execution            | CPU Only            |
| Interface            | Command Line        |

---

# System Requirements

## Minimum Requirements

* Windows 10/11
* 8GB RAM
* C++ Compiler (MinGW g++)
* llama.cpp build
* TinyLlama GGUF model

---

# Folder Structure

```text
RAG_QA/
│
├── data/
│   └── docs.txt
│
├── src/
│   ├── main.cpp
│   └── prompt.txt
│
├── README.md
│
└── llama.cpp/
```

---

# How It Works

## 1. Document Loading

The system loads local text documents from `docs.txt`.

---

## 2. Text Chunking

Large documents are split into smaller chunks for efficient retrieval.

---

## 3. Preprocessing

The text is preprocessed using:

* lowercasing
* punctuation removal
* tokenization
* stopword filtering

---

## 4. TF-IDF Vectorization

Each document chunk is converted into numerical vectors using TF-IDF.

This allows the system to mathematically compare query relevance.

---

## 5. Cosine Similarity Retrieval

The query vector is compared against all document vectors using cosine similarity.

The most relevant chunks are selected.

---

## 6. Prompt Construction

Retrieved chunks are combined with the user query to create a grounded prompt.

Example:

```text
Context:
[Retrieved Chunks]

Question:
[User Query]

Answer:
```

---

## 7. Local LLM Inference

The prompt is passed to TinyLlama through llama.cpp for answer generation.

The entire process runs locally without internet or cloud APIs.

---

# Hallucination Reduction

One of the important parts of this project is hallucination control.

The system uses a similarity threshold.

If no retrieved chunk crosses the relevance threshold, the model is not allowed to generate an answer.

Example:

```text
No relevant context found.
```

This prevents unrelated or fabricated responses for out-of-domain questions.

---

# Example Queries

## Valid Domain Queries

```text
what is inheritance
what is encapsulation
what is polymorphism
what are containers in STL
```

## Out-of-Domain Queries

```text
what is machine learning
who is virat kohli
purpose of cell wall
```

---

# Sample Output

```text
Ask your question (/exit to quit): what is inheritance

Top Retrieved Chunks:
Chunk 6 | Score: 0.672436

Running TinyLlama...

Inheritance allows one class to acquire properties and behavior from another class. It promotes code reusability and logical hierarchy in object-oriented programming.
```

---

# Compilation & Execution

## Step 1: Navigate to Source Directory

```bash
cd src
```

## Step 2: Compile

```bash
g++ main.cpp -o main
```

## Step 3: Run

```bash
main
```

---

# Design Philosophy

This project intentionally avoids:

* heavy AI frameworks
* cloud APIs
* GPU dependency
* complex infrastructure

The objective is:

> Understanding the core mechanics of Retrieval-Augmented Generation in the simplest possible way.

---

# Challenges Faced

During development, several practical issues were solved:

* llama.cpp command execution on Windows
* TinyLlama integration
* prompt construction
* interactive mode handling
* retrieval threshold tuning
* local inference management
* hallucination reduction

These challenges helped improve understanding of low-level AI system integration.

---

# Current Limitations

* TF-IDF retrieval lacks deep semantic understanding
* Small model limitations (TinyLlama)
* Limited dataset size
* CLI-only interface
* No vector database integration yet

---

# Future Improvements

Possible future enhancements include:

* Embedding-based retrieval
* FAISS vector database
* ChromaDB integration
* GPU acceleration
* Multi-document support
* Web interface
* Streaming output
* Better prompt engineering
* Larger quantized models
* Hybrid search systems

---

# Learning Outcomes

This project helped in understanding:

* Retrieval-Augmented Generation (RAG)
* TF-IDF vectorization
* cosine similarity
* prompt grounding
* local LLM execution
* llama.cpp integration
* document retrieval systems
* lightweight AI architecture

---

# Authors

## Saurav Chakraborty

B.Tech Student

---

# Acknowledgements

* llama.cpp
* TinyLlama
* Open-source AI community

---

# Final Note

This project is not intended to be a production-scale AI system.

Instead, it focuses on:

* learning
* implementation from scratch
* lightweight execution
* explainable architecture
* understanding the foundations of RAG systems

---

# License

This project is developed for educational and learning purposes.
