//
// Created by milleraa on 10/29/2024.
//

#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <iostream>
#include "Map.h"

class View {
public:
    View();
    ~View();
    char getInput(const std::vector<char>& validChars);
    void printState(const std::vector<char>& directions,
        const std::vector<std::string>& inventory);
    void printMessages(const std::vector<std::string>& msg);
    void printMap(Map* map);
    void printLine(const std::string& line);
};

#endif // VIEW_H
