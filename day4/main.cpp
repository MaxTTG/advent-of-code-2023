#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <set>
#include <vector>
#include <math.h>

struct Card {
    Card() = default;
    Card(int n, std::vector<int> f, std::set<int> s, int nWN) : firstPart(f), secondPart(s) {
        firstPart = f;
        secondPart = s;
    }
    int number;
    std::vector<int> firstPart;
    std::set<int> secondPart;
    int numWiningNumbers;
};

std::vector<Card> parseGame(std::ifstream& fin) {
    std::vector<Card> game;
    std::string temp;
    /* 
     * if we can't read "temp" from "fin"
     * reading will return "false"
     */
    while (fin >> temp) {
        Card card;
        fin >> temp;
        card.number = std::stoi(temp);
        while (true) {
            fin >> temp;
            if (temp == "|")
                break;
            card.firstPart.push_back(std::stoi(temp));
        }
        int k = 0;
        while (true) {
            fin >> temp;
            card.secondPart.insert(std::stoi(temp));
            if (fin.peek() == '\n' || fin.eof())
                break;
        }
        int n = 0;
        for (auto val : card.firstPart) {
            if (card.secondPart.count(val))
                ++n;
        }
        card.numWiningNumbers = n;
        game.push_back(card);
    }
    return game;
}

int gameScore(const std::vector<Card>& game) {
    int ans = 0;
    for (auto card : game) {
        if (card.numWiningNumbers) 
            ans += (1 << (card.numWiningNumbers - 1));
    }
    return ans;
}

int cardScore(const std::vector<Card>& game, std::vector<int> start) {
    for (int i = 0; i < start.size(); ++i) {
        if (i >= 0)
        {
            std::cout << "card " << i << ": " << game[i].numWiningNumbers << "; ";
        }
        
        for (int j = 1; j <= game[i].numWiningNumbers && i + j < game.size(); ++j) {
            start[i + j] += start[i];
        }
        std::cout << "cards was: " << start[i] << " cards added: " << start[i] * game[i].numWiningNumbers << std::endl;
    }
    return std::accumulate(start.begin(), start.end(), 0);
}

int main(){
    std::ifstream fin;
    fin.open("/root/AdventOfCode2023/day4/input.txt");
    if (fin.is_open()) {
        auto game = parseGame(fin);
        int score1 = gameScore(game);

        std::vector<int> start(game.size(), 1);

        int score2 = cardScore(game, start);

        std::cout << "Day 4, Part 1: " << score1 << std::endl;
        std::cout << "Day 4, Part 2: " << score2 << std::endl;
    } else {
        std::cout << "Something wrong :(" << std::endl;
    }
    fin.close();
    return 0;
}
