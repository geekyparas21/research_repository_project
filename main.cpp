#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include<bits/stdc++.h>
using namespace std;

// ======================
// Trie Node for Topic Suggestion
// ======================
struct TrieNode {
    map<char, TrieNode*> children; // links to child nodes based on characters
    bool isEndOfWord;              // marks end of a topic word

    TrieNode() : isEndOfWord(false) {}
};

// ======================
// Trie Class - used for prefix-based topic suggestions
// ======================
class Trie {
private:
    TrieNode* root;

    // Depth First Search to collect all words from current Trie node
    void dfs(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord) results.push_back(prefix);
        for (auto& [ch, child] : node->children) {
            dfs(child, prefix + ch, results);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    // Insert a topic word into the Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c])
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    // Suggest topic words that start with the given prefix
    vector<string> suggestTopics(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c])
                return {}; // no such prefix in the Trie
            node = node->children[c];
        }

        vector<string> suggestions;
        dfs(node, prefix, suggestions);
        return suggestions;
    }
};

// ======================
// Paper Class - holds information about a research paper
// ======================
struct Paper {
    int id;
    string title;
    string topic;
    int citations;

    Paper(int i, string t, string tp) : id(i), title(t), topic(tp), citations(0) {}
};

// ======================
// Research Repository - handles all operations on papers and citations
// ======================
class ResearchRepo {
private:
    unordered_map<int, Paper*> papers;               // paper ID → Paper object
    unordered_map<int, vector<int>> citationGraph;   // paper ID → list of cited papers
    unordered_map<int, int> citationCount;           // paper ID → citation count
    Trie topicTrie;                                  // Trie for topic suggestions

public:
    // Add a paper with title and topic
    void addPaper(int id, const string& title, const string& topic) {
        papers[id] = new Paper(id, title, topic);
        topicTrie.insert(topic); // Add topic to Trie for suggestions
    }

    // Add a citation from one paper to another
    void addCitation(int from, int to) {
        citationGraph[from].push_back(to);
        citationCount[to]++;             // Update citation count map
        if (papers.count(to))            // Also update citation in Paper object
            papers[to]->citations++;
    }

    // Return top K most cited papers
    vector<int> getMostCited(int topK) {
        priority_queue<pair<int, int>> maxHeap;

        // Build max-heap using citation count
        for (auto& [id, count] : citationCount) {
            maxHeap.push({count, id});
        }

        // Extract topK papers with most citations
        vector<int> topPapers;
        while (topK-- && !maxHeap.empty()) {
            topPapers.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return topPapers;
    }

    // Find a path of citations from one paper to another (BFS)
    vector<int> getCitationPath(int from, int to) {
        unordered_map<int, int> parent;     // child → parent
        queue<int> q;
        unordered_set<int> visited;

        q.push(from);
        visited.insert(from);

        while (!q.empty()) {
            int curr = q.front(); q.pop();

            if (curr == to) break;

            for (int neighbor : citationGraph[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    parent[neighbor] = curr;
                    q.push(neighbor);
                }
            }
        }

        // If there’s no path
        if (!parent.count(to)) return {};

        // Reconstruct path from `to` to `from`
        vector<int> path;
        for (int at = to; at != from; at = parent[at])
            path.push_back(at);
        path.push_back(from);
        reverse(path.begin(), path.end());
        return path;
    }

    // Suggest topics by prefix using the Trie
    vector<string> suggestTopics(const string& prefix) {
        return topicTrie.suggestTopics(prefix);
    }

    // Print paper details
    void printPaper(int id) {
        if (!papers.count(id)) {
            cout << "Paper not found\n";
            return;
        }
        Paper* p = papers[id];
        cout << "ID: " << p->id
             << ", Title: " << p->title
             << ", Topic: " << p->topic
             << ", Citations: " << p->citations << endl;
    }
};

// ======================
// Example Usage
// ======================
int main() {
    ResearchRepo repo;

    // Add some papers
    repo.addPaper(1, "Neural Networks", "AI");
    repo.addPaper(2, "Decision Trees", "AI");
    repo.addPaper(3, "Quantum Computing", "Physics");

    // Create citation graph
    repo.addCitation(1, 2); // Paper 1 cites Paper 2
    repo.addCitation(2, 3); // Paper 2 cites Paper 3

    // Print paper info
    repo.printPaper(2);  // Should show: Title = Decision Trees, Citations = 1

    // Show top 2 most cited papers
    cout << "Top cited: ";
    for (int id : repo.getMostCited(2)) cout << id << " ";
    cout << endl;

    // Show citation path from Paper 1 to Paper 3
    cout << "Citation Path 1 -> 3: ";
    for (int id : repo.getCitationPath(1, 3)) cout << id << " ";
    cout << endl;

    // Suggest topics starting with 'A'
    cout << "Suggested Topics for 'A': ";
    for (string t : repo.suggestTopics("A")) cout << t << " ";
    cout << endl;

    return 0;
}
