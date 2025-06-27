#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include<bits/stdc++.h>;
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, string str, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = str;
    buildCodes(root->left, str + "0", codes);
    buildCodes(root->right, str + "1", codes);
}

void compress(string inputPath, string outputPath) {
    ifstream in(inputPath, ios::binary);
    ofstream out(outputPath, ios::binary);
    unordered_map<char, int> freq;

    char ch;
    while (in.get(ch)) freq[ch]++;
    in.clear();
    in.seekg(0);

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto p : freq) pq.push(new Node(p.first, p.second));

    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* node = new Node('\0', l->freq + r->freq);
        node->left = l; node->right = r;
        pq.push(node);
    }

    unordered_map<char, string> codes;
    buildCodes(pq.top(), "", codes);

    // Write the codes as header
    out << codes.size() << '\n';
    for (auto& pair : codes) {
        out << pair.first << ' ' << pair.second << '\n';
    }

    // Encode the file
    string encoded = "";
    while (in.get(ch)) encoded += codes[ch];

    int extra = 8 - encoded.size() % 8;
    encoded.append(extra, '0');

    out << extra << '\n';

    for (size_t i = 0; i < encoded.size(); i += 8) {
        bitset<8> b(encoded.substr(i, 8));
        out.put(b.to_ulong());
    }

    in.close();
    out.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: huffman <inputFile> <outputFile>\n";
        return 1;
    }
    compress(argv[1], argv[2]);
    return 0;
}
