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
        cout << "0. Exit" << endl;
        cout << "1. Display bugs" << endl;
        cout << "2. Find bug" << endl;
        cout << "3. Bug history" << endl;
        cout << "4. Display cells" << endl;
        cout << "5. Tap board" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                return 0; // Exit the program
            case 1:
                board->getBugs();
                break;
            case 2:
                cout << "Enter bug id: ";
                int id;
                cin >> id;
                board->findBug(id);
                break;
            case 3:
                board->displayBugHistory();
                break;
            case 4:
                board->displayCells();
                break;
            case 5:
                // Start simulation
                while (board->countBugs() !=
                       1) {
                    // Perform bug movements
                    board->tapBoard();
                    // Wait for one second before the next simulation step
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }

                // Write endgame history
                writeFile(board);

                delete board;

                return 0; // Exit after simulation ends
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







