#include <string>
#pragma once

struct Piece {
    int buffer;     /// 0 = original / 1 = add
    int start;      /// start position in the buffer
    int length;
    int newlines = 0;

    bool lastIsNewline = 0;

    Piece();
    Piece(int _buffer, int _start, int _length, int _newlines, int l);
};

struct Node{
    Piece piece;

    Node *L = nullptr;
    Node *R = nullptr;

    int priority;

    int subtreeSize;        /// number of characters in a nodes subtree
    int subtreeNewlinesSize;

    bool lastIsNewline;

    Node(Piece p);
};

struct PieceTable{
    std::string originBuffer;                               /// only modified on rebuild
    std::string addBuffer;                                  /// modified after each change to the text

    int originBufferNewlines[10005];
    int addBufferNewlines[10005];

    Node* root = nullptr;                                   /// Implicit Treap Root Node

    int lastInsertPosition = -1;                            /// Position where last insertion happened
    Node* lastInsertNode = nullptr;

    PieceTable(std::string& initial);
    int size(Node* node);                                   /// count number of characters in the subtree of node
    int sizeNewlines(Node* node);
    void pull(Node* node);                                  /// pull dp values into a node

    Node* merge(Node* a, Node* b);                          /// merge two treaps (keys of a < keys of b!)
    void split(Node* node, int key, Node*& a, Node*& b);    /// split a treap into two treaps such that key of a <= key < key of b
    Node* insertPiece(Piece& p, int pos);                    /// insert a piece into the treap
    void getTree(Node* node);                               /// Return the word stored in the subtree of node
    void insertAddBuffer(std::string& add);
    int findRowColPosition(Node* node, int row, int col, int addedRows);
    void bubbleUpdate(Node* node, int pos);
    void insertCharacter(char c, int row, int col);

    void printTree(Node* node);
};
