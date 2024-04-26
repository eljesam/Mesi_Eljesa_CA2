#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Bomber.h"
#include "Bug.h"

using namespace std;

Board::Board() {
    cells = vector<vector<string>>(10, vector<string>(10, " "));
}
void Board::displayBugs(Bug *bug) {
    string direction;
    switch (bug->getDirection()) {
        case 1:
            direction = "NORTH";
            break;
        case 2:
            direction = "EAST";
            break;
        case 3:
            direction = "SOUTH";
            break;
        case 4:
            direction = "WEST";
            break;
    }
    string alive;
    if (bug->isAlive()) {
        alive = "ALIVE";
    } else {
        alive = "DEAD";
    }
    cout << "Bug ID: " << bug->getId() << endl;
    cout << "Bug Type: " << bug->getBugType() << endl;
    cout << "Position: " << bug->getPosition().first << ", " << bug->getPosition().second << endl;
    cout << "Direction: " << bug->getDirection() << endl;
    cout << "Size: " << bug->getSize() << endl;
    cout << "Alive: " << bug->isAlive() << endl;
    cout << "Path: ";
    for (auto &i : bug->getPath()) {
        cout << "(" << i.first << ", " << i.second << ") ";
    }
    cout << endl;
    cout << "Killer ID: " << bug->getKillerId() << endl;
    cout << endl;

    if (bug->getBugType() == "Crawler" || bug->getBugType() == "Bomber") {
        cout << bug->getId() << " " << bug->getBugType() << " (" << bug->getPosition().first << ","
             << bug->getPosition().second << ") " << direction << " " << bug->getSize() << " "
             << alive << endl;
    } else if (bug->getBugType() == "Hopper") {
        cout << bug->getId() << " " << bug->getBugType() << " (" << bug->getPosition().first << ","
             << bug->getPosition().second << ") " << direction << " " << bug->getSize() << " "
             << alive << " " << dynamic_cast<Hopper *>(bug)->getHopLength() << endl;
}
    void Board::findBug(int id) {
        for (auto &bug : bugs) {
            if (bug->getId() == id) {
                displayBugs(bug);
                return;
            }
        }
        cout << "Bug not found" << endl;
    }
    void Board::displayBugHistory() {
        int id;
        cout << "Enter bug ID: ";
        cin >> id;
        for (auto &bug : bugs) {
            if (bug->getId() == id) {
                for (auto &position : bug->getPath()) {
                    cout << position.first << " " << position.second << endl;
                }
                return;
            }
        }
        cout << "Bug not found" << endl;
    }
    void Board::displayCells() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout << cells[i][j] << " ";
            }
            bool bugOnBoard = false;
            for (auto &bug : bugs) {
                if (bug->getPosition().first == i && bug->getPosition().second == j) {
                    cout << bug->getBugType() << " " << bug->getId() << " ";
                    bugOnBoard = true;
                }
            }
            if (!bugOnBoard) {
                cout << "Board empty";
            }
        }
    }
    void Board::tapBoard() {
        moveBugs();
        fight();

        displayCells();
        getBugs();
    }
    void Board::moveBugs() {
        for (auto &bug : bugs) {
            if (bug->isAlive()) {
                bug->move();
            }
        }
    }
    void Board::fight() {
       vector<Bug *> deadBugs;
        for (auto &bug : bugs) {
            if (bug->isAlive()) {
                for (auto &otherBug : bugs) {
                    if (bug->getId() != otherBug->getId() && otherBug->isAlive() && bug->getPosition() == otherBug->getPosition()) {
                        if (bug->getSize() > otherBug->getSize()) {
                            otherBug->setAlive(false);
                            otherBug->setKillerId(bug->getId());
                            deadBugs.push_back(otherBug);
                        } else {
                            bug->setAlive(false);
                            bug->setKillerId(otherBug->getId());
                            deadBugs.push_back(bug);
                        }
                        //if bug is bomber and it comes in contact with another bug, it explodes and kills the other bug no matter the size
                        if (bug->getBugType() == "Bomber") {
                            otherBug->setAlive(false);
                            otherBug->setKillerId(bug->getId());
                            deadBugs.push_back(otherBug);
                        }
                    }
                }
            }
        }
        for (auto &deadBug : deadBugs) {
            cout << "Bug " << deadBug->getId() << " has been killed by bug " << deadBug->getKillerId() << endl;
        }

    }
    void Board::addBug(Bug *bug) {
        bugs.push_back(bug);
    }
    void Board::getBugs() {
        for (auto &bug : bugs) {
            displayBugs(bug);
        }
    }
    int Board::countBugs() {
        int count = 0;
        for (auto &bug : bugs) {
            if (bug->isAlive()) {
                count++;
            }
        }
    }
    vector<vector<Bug *>> Board::getBugsVector() {
        vector<vector<Bug *>> bugsVector;
        for (int i = 0; i < 10; i++) {
            vector<Bug *> row;
            for (int j = 0; j < 10; j++) {
                for (auto &bug : bugs) {
                    if (bug->getPosition().first == i && bug->getPosition().second == j) {
                        row.push_back(bug);
                    }
                }
            }
            bugsVector.push_back(row);
        }
        return bugsVector;
    }

}


