#include "PieceTable.h"
#include <algorithm>
#include <iostream>

int countNewlines(std::string& initial){
    return count(initial.begin(), initial.end(), '\n');
}

Piece::Piece(){
    buffer = 0;
    start = 0;
    length = 0;
    newlines = 0;
}

Piece::Piece(int _buffer, int _start, int _length, int _newlines, int l){
    buffer = _buffer;
    start = _start;
    length = _length;
    newlines = _newlines;
    lastIsNewline = l;
}

Node::Node(Piece p){
    piece = p;
    priority = rand();
    subtreeSize = p.length;
    subtreeNewlinesSize = p.newlines;
    lastIsNewline = p.lastIsNewline;
}

PieceTable::PieceTable(std::string& initial){
    originBuffer = initial;
    if (!initial.empty())
        root = new Node(Piece(0, 0, (int)initial.size(), countNewlines(initial), (originBuffer[initial.size()-1] == '\n')));

    originBufferNewlines[0] = 0;
    addBufferNewlines[0] = 0;
    for (size_t i = 1;i <= originBuffer.size();i++)
        originBufferNewlines[i] = originBufferNewlines[i-1] + (originBuffer[i-1] == '\n');
}

int PieceTable::size(Node* node){
    return node ? node->subtreeSize : 0;
}

int PieceTable::sizeNewlines(Node* node){
    return node ? node->subtreeNewlinesSize : 0;
}

void PieceTable::pull(Node* node){
    if (!node) return;

    node->subtreeSize = size(node->L) + size(node->R) + node->piece.length;
    node->subtreeNewlinesSize = sizeNewlines(node->L) + sizeNewlines(node->R) + node->piece.newlines;
    if (!node->R)
        node->lastIsNewline = node->piece.lastIsNewline;
    else
        node->lastIsNewline = node->R->lastIsNewline;
}

Node* PieceTable::merge(Node* a, Node* b){
    if (!a) return b;
    if (!b) return a;
    if (a->priority > b->priority){
        a->R = merge(a->R,b);
        pull(a);
        return a;
    }

    b->L = merge(a,b->L);
    pull(b);
    return b;
}

void PieceTable::split(Node* node, int key, Node*& a, Node*& b){
    if (!node){
        a = b = nullptr;
        return;
    }

    int leftSize = size(node->L);
    int pieceEnd = leftSize + node->piece.length;

    if (key <= leftSize){
        split(node->L, key, a, node->L);
        b = node;
        pull(b);
    }
    else if (key > pieceEnd){
        split(node->R, key - pieceEnd, node->R, b);
        a = node;
        pull(a);
    }
    else {
        int offset = key - leftSize;

        if (offset == node->piece.length){
            b = node->R;
            node->R = nullptr;
            a = node;
            pull(a);
        }
        else {
            Piece p1 = node->piece;
            Piece p2 = node->piece;

            p1.length = offset;

            p2.start += offset;
            p2.length -= offset;

            /// Newline Cnt

            p1.newlines = (p1.buffer ? addBufferNewlines[p1.start + p1.length] : originBufferNewlines[p1.start + p1.length]) -
                          (p1.buffer ? addBufferNewlines[p1.start] : originBufferNewlines[p1.start]);
            p2.newlines = (p2.buffer ? addBufferNewlines[p2.start + p2.length] : originBufferNewlines[p2.start + p2.length]) -
                          (p2.buffer ? addBufferNewlines[p2.start] : originBufferNewlines[p2.start]);

            Node* leftPiece = new Node(p1);
            Node* rightPiece = new Node(p2);

            a = merge(node->L,leftPiece);
            b = merge(rightPiece,node->R);

            delete node;
        }
    }
}

Node* PieceTable::insertPiece(Piece& p, int pos){
    if (pos > size(root)){
        std::cout << "Invalid Piece Insertion!\n";
        return nullptr;
    }
    Node* newNode = new Node(p);

    Node* a; Node* b;
    split(root, pos, a, b);
    root = merge(merge(a,newNode),b);
    return newNode;
}

void PieceTable::getTree(Node* node){
    if (!node)
        return;

    if (node->L != nullptr)
        getTree(node->L);

    Piece piece = node->piece;
    for (int i = piece.start;i <= piece.start+piece.length-1;i++)
        std::cout << (piece.buffer ? addBuffer[i] : originBuffer[i]);

    if (node->R != nullptr)
        getTree(node->R);
}

void PieceTable::insertAddBuffer(std::string& add){
    int originalSize = addBuffer.size();
    addBuffer.append(add);

    if (originalSize == 0)
        addBufferNewlines[0] = 0;
    for (int i = originalSize+1;i <= (int)addBuffer.size();i++)
        addBufferNewlines[i] = addBufferNewlines[i-1] + (addBuffer[i-1] == '\n');
}

int PieceTable::findRowColPosition(Node* node, int row, int col, int addedRows){

    if (row < 0 || col < 0)
        return -1;

    int totalSize = size(node);
    int totalNewlines = sizeNewlines(node);

    if (row > totalNewlines)
        return -1;

    int startPos = 0;
    int endPos = totalSize;

    for (int target = row; target <= row + 1; target++){

        if (target == 0 || target > totalNewlines)
            continue;

        Node* cur = node;
        int k = target;
        int base = 0;
        int newlinePos = -1;

        while (cur){

            int leftSize = size(cur->L);
            int leftNewlines = sizeNewlines(cur->L);

            if (k <= leftNewlines){
                cur = cur->L;
                continue;
            }

            k -= leftNewlines;

            if (k <= cur->piece.newlines){

                int st = 1;
                int dr = cur->piece.length;
                int offset = -1;
                int start = cur->piece.start;

                while (st <= dr){

                    int mid = (st + dr) / 2;

                    int val = cur->piece.buffer
                        ? addBufferNewlines[start + mid] - addBufferNewlines[start]
                        : originBufferNewlines[start + mid] - originBufferNewlines[start];

                    if (val >= k){
                        offset = mid;
                        dr = mid - 1;
                    }
                    else{
                        st = mid + 1;
                    }
                }

                if (offset == -1)
                    return -1;

                newlinePos = base + leftSize + offset - 1;
                break;
            }

            k -= cur->piece.newlines;

            base += leftSize + cur->piece.length;
            cur = cur->R;
        }

        if (newlinePos == -1)
            return -1;

        if (target == row)
            startPos = newlinePos + 1;
        else
            endPos = newlinePos;
    }

    if (startPos + col > endPos)
        return -1;

    return startPos + col;
}

void PieceTable::bubbleUpdate(Node* node, int pos){
    if (!node)
        return;

    int leftSize = size(node->L);
    int pieceEnd = leftSize + node->piece.length;

    if (pos <= leftSize)
        bubbleUpdate(node->L,pos);
    else if (pos > pieceEnd)
        bubbleUpdate(node->R,pos - pieceEnd);

    pull(node);
}

void PieceTable::insertCharacter(char c, int row, int col){
    int pos = findRowColPosition(root, row, col, 0);

    if (pos == -1){
        std::cout << "Invalid insert position!\n";
        return;
    }


    std::string aux = "";
    aux.append(&c,1);

    insertAddBuffer(aux);
    if (lastInsertPosition != -1 && pos == lastInsertPosition+1){
        lastInsertPosition++;

        lastInsertNode->piece.length++;
        lastInsertNode->piece.newlines += (c == '\n');

        lastInsertNode->piece.lastIsNewline = (c == '\n');

        bubbleUpdate(root,pos);

        return;
    }

    Piece newPiece(1, addBuffer.size()-1, 1, (c == '\n'), (c == '\n'));


    lastInsertNode = insertPiece(newPiece, pos);
    lastInsertPosition = pos;
}

void PieceTable::printTree(Node* node){
    if (!node)
        return;

    if (node->L != nullptr){
        std::cout << "L";
        printTree(node->L);
    }

    Piece piece = node->piece;
    std::cout << piece.buffer << " " << piece.start << " " << piece.length << " " << piece.newlines << "\n";

    if (node->R != nullptr){
        std::cout << "R";
        printTree(node->R);
    }
}
