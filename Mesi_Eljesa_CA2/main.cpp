#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <thread>
#include <cstring>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Bomber.h"
#include "Board.h"


using namespace std;


void readFromFile(Board *board);

void parseLine(const string &strline, Board *board);

void writeFile(Board *board);

int main() {
    auto *board = new Board();
    readFromFile(board);

    while (true) {
        cout << "0. Start Fight" << endl;
        cout << "1. Display bugs" << endl;
        cout << "2. Find bug" << endl;
        cout << "3. Bug history" << endl;
        cout << "4. Display cells" << endl;
        cout << "5. See Bugs Total" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
              //start fight
                board->tapBoard();
                break;
            case 1:
                // Display bugs
                board->getBugs();
                break;
            case 2:
                // Find bug
                int id;
                cout << "Enter bug id: ";
                cin >> id;
                board->findBug(id);
                break;
            case 3:
                // Bug history
                int id2;
                cout << "Enter bug id: ";
                cin >> id2;
                board->displayBugHistory(id2);
                break;
            case 4:
                // Display cells
                board->displayCells();
                break;
            case 5:
                // See Bugs Total
                 cout << "Total bugs: " << board->countBugs() << endl;
                break;
            case 6:
                // Exit


                writeFile(board);

                delete board;

                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }

    return 0;
}

void readFromFile(Board *board) {
    ifstream inFileStream("bugs.txt");

    if (inFileStream) {
        string line;

        while (getline(inFileStream, line)) {
            parseLine(line, board);
        }

        inFileStream.close();
    } else {
        cout << "Error opening file" << endl;
        if(errno){
            cout << strerror(errno) << endl;
        }
    }
}

void parseLine(const string &strline, Board *board) {
    stringstream strSteam(strline);

    const char delim = ';';
    string type;
    getline(strSteam, type, delim);
    string temp;

    try {
        if (type == "C") {
            int id;
            pair<int, int> position;
            int direction;
            int size;
            getline(strSteam, temp, delim);
            id = stoi(temp);
            getline(strSteam, temp, delim);
            position.first = stoi(temp);
            getline(strSteam, temp, delim);
            position.second = stoi(temp);
            getline(strSteam, temp, delim);
            direction = stoi(temp);
            getline(strSteam, temp, delim);
            size = stoi(temp);
            auto *crawler = new Crawler(id, position, direction, size);
            board->addBug(crawler);
        } else if (type == "H") {
            int id;
            pair<int, int> position;
            int direction;
            int size;
            int hopLength;
            getline(strSteam, temp, delim);
            id = stoi(temp);
            getline(strSteam, temp, delim);
            position.first = stoi(temp);
            getline(strSteam, temp, delim);
            position.second = stoi(temp);
            getline(strSteam, temp, delim);
            direction = stoi(temp);
            getline(strSteam, temp, delim);
            size = stoi(temp);
            getline(strSteam, temp, delim);
            hopLength = stoi(temp);
            auto *hopper = new Hopper(id, position, direction, size, hopLength);
            board->addBug(hopper);
        } else if (type == "B") {
            int id;
            pair<int, int> position;
            int direction;
            int size;
            getline(strSteam, temp, delim);
            id = stoi(temp);
            getline(strSteam, temp, delim);
            position.first = stoi(temp);
            getline(strSteam, temp, delim);
            position.second = stoi(temp);
            getline(strSteam, temp, delim);
            direction = stoi(temp);
            getline(strSteam, temp, delim);
            size = stoi(temp);
            auto *bomber = new Bomber(id, position, direction, size);
            board->addBug(bomber);
        } else {
            cout << "Invalid type" << endl;
        }
    }
    catch (std::invalid_argument const &e) {
        cout << "Invalid argument" << endl;
    }
    catch (std::out_of_range const &e) {
        cout << "Out of range" << endl;
    }
    catch (...) {
        cout << "Error" << endl;
    }
}
void writeFile(Board *board) {
    ofstream outFileStream("simHistory.txt");

    if (outFileStream) {
        for (auto &bug : board->getBugsVector()) {
            if (bug.size() == 1) {
                outFileStream << bug[0]->getId() << " " << bug[0]->getBugType() << " wins" << endl;
            }
        }

        outFileStream.close();
    } else {
        cout << "Error opening file" << endl;
    }
}







