//
// Created by milleraa on 10/29/2024.
//

#include "View.h"

View::View() {
}

View::~View() {
}

char View::getInput(const std::vector<char> &validChars) {
    //ask for input until valid input is given
    char input;
    bool valid = false;
    while (!valid) {
        std::cin >> input;

        auto iter = validChars.begin();
        while (iter != validChars.end() && !valid) {
            if (input == *iter) {
                valid = true;
            }
            ++iter;
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
    std::cout <<
    "+---+       +---+---+   +---+---+" << "\n"
    "|   |       |     ! |<O>| !     |" << "\n"
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
    "|       |   |       |       |   |" << "\n"
    "+---+---+   +---+---+       +---+"
    << std::endl;
}

void View::printLine(const std::string &line) {
}