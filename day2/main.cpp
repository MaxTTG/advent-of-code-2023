#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <map>
#include <numeric>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

std::regex gamePattern("Game (\\d+):");
std::regex rgbPattern("(\\d+) (red|green|blue)");

std::pair<int, int> parseGame(std::string game) {
    std::pair<int, int> ans;
    std::map<std::string, int> rgb;

    std::smatch match;
    std::regex_search(game, match, gamePattern);
    ans.first = std::stoi(match[1]);
    
    while(std::regex_search(game, match, rgbPattern)) {
        std::string color = match[2];
        int n = std::stoi(match[1]);

        if (n > rgb[color])
            rgb[color] = n;
        
        game = match.suffix().str();
    }

    if (rgb["red"] > RED_MAX || rgb["green"] > GREEN_MAX || rgb["blue"] > BLUE_MAX)
        ans.first = 0;
    ans.second = rgb["red"] * rgb["green"] * rgb["blue"];
    return ans;
}

int main() {
    std::ifstream fin;
    fin.open("/root/AdventOfCode2023/day2/input.txt");
    if (fin.is_open())
    {
        std::vector<int> indexes, powers;
        int sum = 0, pow = 0;
        for (std::string game; std::getline(fin, game);)
        {
            std::pair<int, int> n = parseGame(game);
            if (n.first)
                indexes.push_back(n.first);
            powers.push_back(n.second);
        }
        std::cout << "Day 2, Part 1: " << std::accumulate(indexes.begin(), indexes.end(), 0) << std::endl;
        std::cout << "Day 2, Part 2: " << std::accumulate(powers.begin(), powers.end(), 0) << std::endl;
    } else {
        std::cout << "Something wrong :(" << std::endl;
    }
    fin.close();
    return 0;
}
