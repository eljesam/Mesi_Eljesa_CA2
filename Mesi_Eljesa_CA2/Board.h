//
// Created by eljes on 26/04/2024.
//

#ifndef MESI_ELJESA_CA2_BOARD_H
#define MESI_ELJESA_CA2_BOARD_H
#include<vector>
#include "Bug.h"

class Board {
    private:
        vector<vector<string>> cells;
        vector<Bug*> bugs;
public:
    Board();
    static void displayBugs(Bug *bug);
    void findBug(int id);
    void displayBugHistory();
    void displayCells();
    void tapBoard();
    void addBug(Bug *bug);
    void getBugs();
    int countBugs();

    vector<vector<Bug *>> getBugsVector();

    void moveBugs();
    void fight();
};
#endif //MESI_ELJESA_CA2_BOARD_H
