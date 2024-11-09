//
// Created by milleraa on 10/29/2024.
//

#include "View.h"


View::View() {
    lines = {
        "+---+       +---+---+   +---+---+",
        "|00 |01 |02 |03  04 |05 |06  07 |",
        "+   +---+---+       +---+       +",
        "|10  11  12  13  14  15  16  17 |",
        "+   +---+---+---+---+   +---+   +",
        "|20 |21 |22 |23 |24 |25 |26 |27 |",
        "+   +---+---+---+---+   +---+   +",
        "|30 |31 |32  33 |34 |35 |36 |37 |",
        "+   +---+       +---+   +---+   +",
        "|40 |41 |42  43  44  45 |46 |47 |",
        "+   +---+               +---+   +",
        "|50 |51 |52  53  54  55 |56 |57 |",
        "+   +---+   +---+       +---+   +",
        "|60 |61 |62 |63 |64  65 |66 |67 |",
        "+   +---+   +---+---+---+---+   +",
        "|70 |71 |72 |73 |74 |75 |76 |77 |",
        "+   +---+   +---+---+---+---+   +",
        "|80  81  82  83  84  85  86  87 |",
        "+       +---+       +---+---+   +",
        "|90  91 |92 |93  94 |95 |96 |97 |",
        "+---+---+   +---+---+       +---+"
    };
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
    // Should randomize
    // std::shuffle(msg.begin(), msg.end(), std::random_device()());
    for (const std::string & message : msg) {
        std::cout << message << endl;
    }
}

void View::printMap(Map *map) {
    for (int i = 0; i < lines.size(); i++) {
        if (i % 2 == 0) {
            cout << lines[i] << endl;
        } else {
            std::string line = lines[i];
            for (int j = 0; j < 8; j++) {
                std::string current = to_string((i - 1) / 2) + to_string(j) + " ";
                std::string replacement = map->getRoom((i - 1) / 2, j)->getString();
                line.replace(line.find(current), current.size(), replacement);
            }
            cout << line << endl;
        }
    }
/*
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
*/
}

void View::printLine(const std::string &line) {

}
