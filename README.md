# Research Repository & Citation Manager

A high-performance C++ system designed to manage academic papers, track citation networks using **Graph Theory**, and provide topic suggestions using a **Trie (Prefix Tree)**.

## 🚀 Features

- **Paper Management**: Store and retrieve papers by unique IDs with $O(1)$ average lookup.
- **Citation Graph**: Model relationships between research papers to analyze academic influence.
- **Intelligent Autocomplete**: Prefix-based topic suggestions (e.g., typing "A" suggests "AI", "Algorithms").
- **Citation Analytics**: Identify the "Top K" most influential papers using a Max-Heap.
- **Pathfinding**: Discover the citation chain between two specific papers using Breadth-First Search (BFS).

## 🛠️ Data Structures & Algorithms

This project implements several core computer science concepts:

| Component | Data Structure | Algorithm / Logic |
| :--- | :--- | :--- |
| **Topic Autocomplete** | `Trie` (Prefix Tree) | Depth First Search (DFS) for suggestions |
| **Citation Network** | `Adjacency List` | Directed Graph representation |
| **Search Engine** | `Queue` | Breadth-First Search (BFS) for shortest path |
| **Ranking System** | `Priority Queue` | Max-Heap for $O(N \log K)$ ranking |
| **Paper Storage** | `Hash Map` | `std::unordered_map` for fast indexing |



## 📂 Project Structure

- `main.cpp`: Contains the full source code including the `Trie`, `Paper`, and `ResearchRepo` classes.
- `README.md`: Project documentation and usage guide.

## ⚙️ Installation & Usage

### Prerequisites
- A C++ compiler (GCC/G++, Clang, or MSVC).
- C++11 standard or higher.

### Compiling
Use your terminal to compile the source code:
```bash
g++ -std=c++11 main.cpp -o ResearchManager
