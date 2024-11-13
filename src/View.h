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
        const std::vector<std::string>& inventory,
        std::vector<string> localMap = {"", "", "", ""});
    static void printValidDirections(const std::vector<char>& directions);
    void printMessages(const std::vector<std::string>& msg);

    vector<string> generateLocalMap(Map *map, int x, int y, bool debug);

    void printMap(Map* map);
    void printLine(const std::string& line, bool endline = true);
private:
    std::vector<std::string> lines;
    string maskString(string roomString, bool debug);
};

#endif // VIEW_H
