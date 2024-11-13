//
// Created by milleraa on 10/29/2024.
//

#include "View.h"
#include <optional>
#include <algorithm> // for std::remove

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
#include <unordered_map> // for std::unordered_map

char View::getInput(const std::vector<char> &validChars) {
    char input;
    bool valid = false;
    while (!valid) {
        std::cin >> input;
        input = std::toupper(input);
        valid = false;

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
        const std::vector<std::string> &messages,
        const std::vector<std::string> &inventory,
        const std::vector<string> &localMap) {
    //print directions like N(orth), S(outh), E(ast), W(est)
    std::cout << "Actions: ";
    printValidDirections(directions);
    std::cout << ", ";
    std::cout << "\33[38:5:178mH\33[0m(elp), \33[38:5:12mM\33[0m(ap), ";
    std::cout << "\33[38:5:196mQ\33[0m(uit), \33[38:5:202mU\33[0m(se item), ";
    std::cout << "\33[38:5:110m*\33[0m(settings)" << std::endl;
    printMessages(messages);
    std::cout << "Inventory:" << "    " << localMap[0];
    std::cout << "  " << localMap[1] << std::endl;
    std::cout << inventory[0] << "   " << "            ";
    std::cout << localMap[2] << std::endl;
    std::cout << inventory[1] << "      " << "            ";
    std::cout << localMap[3] << std::endl;
}

/**
 * Prints the valid directions corresponding to the direction list passed in.
 * Prints all on the same line, no endl
 * @param directions a list of chars, either N, S, E or W.
 */
void View::printValidDirections(const std::vector<char> &directions) {
    std::unordered_map<char, std::string> directionMap = {
        {'N', "\33[38:5:10mN\33[0m(orth)"},
        {'S', "\33[38:5:10mS\33[0m(outh)"},
        {'E', "\33[38:5:10mE\33[0m(ast)"},
        {'W', "\33[38:5:10mW\33[0m(est)"}
    };
    std::vector<std::string> validDirections;
    for (const char &direction : directions) {
        validDirections.push_back(directionMap[direction]);
    }

    for (size_t i = 0; i < validDirections.size(); ++i) {
        std::cout << validDirections[i];
        if (i < validDirections.size() - 1) {
            std::cout << ", ";
        }
    }
}

void View::printMessages(const std::vector<std::string> &msg) {
    // Should randomize
    // std::shuffle(msg.begin(), msg.end(), std::random_device()());
    for (const std::string &message : msg) {
        std::cout << "\33[3m" << message << "\33[0m" << std::endl;
    }
}

vector<string> View::generateLocalMap(Map *map, int x, int y, bool debug) {
    vector<string> localMap = {"Local Map:"};
    for (int Y = y - 1; Y <= y + 1; Y++) {
        string line = "|";
        for (int X = x - 1; X <= x + 1; X++) {
            if (map->validRoom(X, Y)) {
                std::string roomString = map->getRoom(X, Y)->getString();
                roomString = maskString(roomString, debug);
                line += roomString;
            } else {
                line += "X";
            }
        }
        localMap.push_back(line + "|");
    }
    return localMap;
}

string View::maskString(string roomString, bool debug) {
    //replace "XXX" with " X "
    unordered_map<string, string> debugMap = {
        {"XXX", " X "},
        {"<O>", " C "},
        {"   ", " . "},
    };
    unordered_map<string, string> replaceMap = {
        {"XXX", " X "},
        {"<O>", " C "},
        {" ~ ", "\33[0m . "},
        {" H ", "\33[0m . "},
        {" # ", "\33[0m . "},
        {" > ", "\33[0m . "},
        {"   ", " . "}
    };
    const unordered_map<string, string> mapSource = debug ? debugMap : replaceMap;
    for (const auto &pair : mapSource) {
        size_t pos = 0;
        while ((pos = roomString.find(pair.first, pos)) != std::string::npos) {
            roomString.replace(pos, pair.first.length(), pair.second);
            pos += pair.second.length();
        }
    }
    //replace all " "'s with ""
    roomString.erase(std::remove(
        roomString.begin(), roomString.end(), ' '),
        roomString.end());

    return roomString;
}

void View::printMap(Map *map) {
    for (int i = 0; i < lines.size(); i++) {
        if (i % 2 == 0) {
            std::cout << lines[i] << std::endl;
        } else {
            std::string line = lines[i];
            for (int j = 0; j < 8; j++) {
                std::string current = to_string((i - 1) / 2) + to_string(j) + " ";
                std::string replacement = map->getRoom(j, (i - 1) / 2)->getString();
                line.replace(line.find(current), current.size(), replacement);
            }
            std::cout << line << std::endl;
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

void View::printLine(const std::string &line, bool endline) {
    cout << line;
    if (endline) {
        cout << std::endl;
    }
}
