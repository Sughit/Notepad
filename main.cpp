#include <iostream>
#include "PieceTable.h"
#include "SaveLoad.h"

int main()
{
    std::string word = "Hello\nWorld!\n";

    PieceTable pieceTable(word);

    pieceTable.printTree(pieceTable.root); std::cout << "\n";
    pieceTable.insertCharacter('C',1,0);
    pieceTable.printTree(pieceTable.root); std::cout << "\n";
    pieceTable.insertCharacter('r',1,1);
    pieceTable.printTree(pieceTable.root); std::cout << "\n";
    pieceTable.insertCharacter('u',1,2);
    pieceTable.printTree(pieceTable.root); std::cout << "\n";
    pieceTable.insertCharacter('e',1,3);
    pieceTable.printTree(pieceTable.root); std::cout << "\n";
    pieceTable.insertCharacter('l',1,4);
    pieceTable.printTree(pieceTable.root); std::cout << "\n";
    pieceTable.insertCharacter('\n',1,5);
    pieceTable.printTree(pieceTable.root); std::cout << "\n";

    pieceTable.getTree(pieceTable.root);
    std::cout << "\n";
    pieceTable.printTree(pieceTable.root);
    return 0;
}
