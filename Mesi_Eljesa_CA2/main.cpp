#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <thread>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Bomber.h"
#include "Board.h"


using namespace std;
void readFromFile();

void parseLine(const string &strline);

void printBug(Bug *bug);

void findBug();

void bugHistory();

void displayCells();

void fight();

void writeFile();

vector<Bug *> bugs_vector;



int main(){
    Board board(10, 10);
    readFromFile();

    while(true) {
        cout << "1. Find bug by ID" << endl;
        cout << "2. Display bug history" << endl;
        cout << "3. Display cells" << endl;
        cout << "4. Fight" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                findBug();
                break;
            case 2:
                bugHistory();
                break;
            case 3:
                displayCells();
                break;
            case 4:
                fight();
                break;
            case 5:
                writeFile();
                return 0;
            default:
                cout << "Invalid choice" << endl;

                while(count_if(bugs_vector.begin(), bugs_vector.end(), [](Bug *bug) { return bug->isAlive(); }) != 1) {
                    for (auto &bug: bugs_vector) {
                        if (bug->isAlive()) {
                            bug->move();
                        }
                    }

                    fight();

                    displayCells();
                    for(auto bug: bugs_vector){
                        printBug(bug);
                    }
                    this_thread::sleep_for(chrono::seconds(1));
                }

                writeFile();
                return 0;


        }
    }

}
void readFromFile() {
    ifstream file("bugs.txt");
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        parseLine(line);
    }
    file.close();
}
void parseLine(const string &strline) {
    stringstream line(strline);

    const char delimiter = ';';
    string type;
    getline(line, type, delimiter);
    string temp;
    try{
      if(type == "C"){
          int id;
          pair<int, int> position;
            int direction;
            int size;
            getline(line, temp, delimiter);
            id = stoi(temp);
            getline(line, temp, delimiter);
            position.first = stoi(temp);
            getline(line, temp, delimiter);
            position.second = stoi(temp);
            getline(line, temp, delimiter);
            direction = stoi(temp);
            getline(line, temp, delimiter);
            size = stoi(temp);
            auto *crawler = new Crawler(id, position, direction, size);
            bugs_vector.push_back(crawler);
      }
        else if(type == "H"){
            int id;
            pair<int, int> position;
                int direction;
                int size;
                int hopLength;
                getline(line, temp, delimiter);
                id = stoi(temp);
                getline(line, temp, delimiter);
                position.first = stoi(temp);
                getline(line, temp, delimiter);
                position.second = stoi(temp);
                getline(line, temp, delimiter);
                direction = stoi(temp);
                getline(line, temp, delimiter);
                size = stoi(temp);
                auto *hopper = new Hopper(id, position, direction, size, hopLength);
                bugs_vector.push_back(hopper);
        }
        else if(type == "B"){
            int id;
            pair<int, int> position;
                int direction;
                int size;
                getline(line, temp, delimiter);
                id = stoi(temp);
                getline(line, temp, delimiter);
                position.first = stoi(temp);
                getline(line, temp, delimiter);
                position.second = stoi(temp);
                getline(line, temp, delimiter);
                direction = stoi(temp);
                getline(line, temp, delimiter);
                size = stoi(temp);
                auto *bomber = new Bomber(id, position, direction, size);
                bugs_vector.push_back(bomber);
        }
        else{
            cout << "Invalid bug type" << endl;
        }
    }
    catch (invalid_argument &e) {
        cout << "Invalid argument: " << e.what() << endl;
    }
    catch (out_of_range &e) {
        cout << "Out of range: " << e.what() << endl;
    }
    catch(...) {
        cout << "Unknown error" << endl;
    }
}
void printBug(Bug *bug){
    string direction;

    if(bug->getDirection() == 1){
        direction = "N";
    }
    else if(bug->getDirection() == 2){
        direction = "E";
    }
    else if(bug->getDirection() == 3){
        direction = "S";
    }
    else if(bug->getDirection() == 4){
        direction = "W";
    }

    string alive;
    if(bug->isAlive()){
        alive = "Alive";
    }
    else{
        alive = "Dead";
    }

    if(bug->getBugType() == "C"){
        cout << "Crawler " << bug->getId() << " " << bug->getPosition().first << " " << bug->getPosition().second << " " << direction << " " << bug->getSize() << " " << alive << endl;
    }
    else if(bug->getBugType() == "H"){
        cout << "Hopper " << bug->getId() << " " << bug->getPosition().first << " " << bug->getPosition().second << " " << direction << " " << bug->getSize() << " " << alive <<" "<<dynamic_cast<Hopper *>(bug)->getHopLength() << endl;
    }
    else if(bug->getBugType() == "B"){
        cout << "Bomber " << bug->getId() << " " << bug->getPosition().first << " " << bug->getPosition().second << " " << direction << " " << bug->getSize() << " " << alive << endl;
    }
}
void findBug(){
    int id;
    cout << "Enter bug ID: ";
    cin >> id;
    for(auto bug: bugs_vector){
        if(bug->getId() == id){
            printBug(bug);
            return;
        }
    }
    cout << "Bug not found" << endl;
}
void bugHistory(){
    int id;
    cout << "Enter bug ID: ";
    cin >> id;
    for(auto bug: bugs_vector){
        if(bug->getId() == id){
            for(auto position: bug->getPath()){
                cout << position.first << " " << position.second << endl;
            }
            return;
        }
    }
    cout << "Bug not found" << endl;
}

void displayCells(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << "(" << i << "," << j << ") ";
            bool bugOnBoard = false;
            for (auto bug: bugs_vector) {
                if (bug->getPosition().first == i && bug->getPosition().second == j) {
                    cout << bug->getBugType() << " " << bug->getId() << " ";
                    bugOnBoard  = true;
                }
            }
            if (!bugOnBoard ) {
                cout << "No bugs on the board";
            }
            cout << endl;
        }
    }
}

void fight(){
    for(auto bug: bugs_vector){
        if(bug->isAlive()){
            for(auto otherBug: bugs_vector){
                if(bug->getId() != otherBug->getId() && otherBug->isAlive() && bug->getPosition() == otherBug->getPosition()){
                    if(bug->getSize() > otherBug->getSize()){
                        otherBug->setAlive(false);
                        bug->setSize(bug->getSize() + otherBug->getSize());
                        bug->setKillerId(bug->getId());
                    }
                    else{
                        bug->setAlive(false);
                        otherBug->setSize(otherBug->getSize() + bug->getSize());
                        otherBug->setKillerId(otherBug->getId());
                    }
                }
            }
        }
    }
}

void writeFile() {
    ofstream file("simHistory.txt");
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }
    else {
        for (auto bug: bugs_vector) {
            file << bug->getId() << " " << bug->getBugType() << "path:";
            for (auto position: bug->getPath()) {
                file << position.first << " " << position.second << " ";
            }
            if (bug->isAlive()) {
                file << "Alive" << endl;
            } else {
                file << "Killed by:" << bug->getKillerId() << endl;
            }

        }
        for (auto bug: bugs_vector) {
            if (bug->isAlive()) {
                file << "Winner: " << bug->getId() << endl;
                break;
            }
        }
        file.close();
    }
}







