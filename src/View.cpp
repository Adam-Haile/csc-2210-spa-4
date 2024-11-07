//
// Created by milleraa on 10/29/2024.
//

#include "View.h"

View::View() {
}

View::~View() {
}

#include <cctype> // for toupper

char View::getInput(const std::vector<char> &validChars) {
    char input;
    bool valid = false;
    while (!valid) {
        std::cin >> input;

        input = std::toupper(input);

        for (const char &validChar : validChars) {
            if (input == std::toupper(validChar)) {
                valid = true;
                break;
            }
        }

        if (!valid) {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return input;
}

void View::printState(const std::vector<char> &directions,
    const std::vector<std::string> &inventory) {
    //print directions like N(orth), S(outh), E(ast), W(est)
    std::cout << "Actions: ";
    for (char dir : directions) {
        switch (dir) {
            case 'N':
                std::cout << "N(orth), ";
                break;
            case 'S':
                std::cout << "S(outh), ";
                break;
            case 'E':
                std::cout << "E(ast), ";
                break;
            case 'W':
                std::cout << "W(est), ";
                break;
            default:
                break;
        }
    }

    std::cout << "H(elp), M(ap), Q(uit)" << std::endl;
    for (std::string item : inventory) {
        std::cout << item << std::endl;
    }
}

void View::printMessages(const std::vector<std::string> &msg) {
}

void View::printMap(Map *map) {
    // Maybe I should just make a template and fill in each square??
    Room* room = nullptr;
    cout << "+---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "|";
        for (int j = 0; j < 8; j++) {
            room = map->getRoom(i, j);
            if (!room->isTraversable)
                cout << "XXX";
            else
                cout << "   ";
            if (j == 7)
                cout << "|";
            else
                cout << " ";
        }
        if (i == 9)
            cout << endl << "+---+---+---+---+---+---+---+---+";
        cout << endl;
    }
    std::cout << endl <<
    "+---+       +---+---+   +---+---+" << "\n"
    "|   |XXX|XXX|     ! |<O>| !     |" << "\n"
    "+   +---+---+       +---+       +" << "\n"
    "|     #           !   !   !     |" << "\n"
    "+   +---+---+---+---+   +---+   +" << "\n"
    "|   |XXX|XXX|XXX|XXX|   |XXX|   |" << "\n"
    "+   +---+---+---+---+   +---+   +" << "\n"
    "| H |XXX|       |XXX|   |XXX|   |" << "\n"
    "+   +---+       +---+   +---+   +" << "\n"
    "|   |XXX|         H     |XXX|   |" << "\n"
    "+   +---+               +---+   +" << "\n"
    "|   |XXX|               |XXX| > |" << "\n"
    "+   +---+   +---+       +---+   +" << "\n"
    "| H |XXX| ! |XXX| !     |XXX|   |" << "\n"
    "+   +---+   +---+---+---+---+   +" << "\n"
    "|   |XXX| ! |<O>|XXX|XXX|XXX|   |" << "\n"
    "+   +---+   +---+---+---+---+   +" << "\n"
    "|         !   !   !       P     |" << "\n"
    "+       +---+       +---+---+   +" << "\n"
    "|       |XXX|       |XXX|XXX|   |" << "\n"
    "+---+---+   +---+---+       +---+"
    << std::endl;
}

void View::printLine(const std::string &line) {
}
