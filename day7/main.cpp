#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

enum struct handType { High, Pair, TPair, Three, FHouse, Four, Five };

std::unordered_map<char, short> Cards = {
    {'j', 0},
    {'2', 2}, 
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};

struct Hand {
    Hand(std::string c, int b) : cards(c), bid(b) {
        std::string temp = cards;
        std::sort(temp.begin(), temp.end(), [](char a, char b) {
            return Cards[a] < Cards[b];
        });
        char t = temp[0];
        int i = 0;
        std::vector<int> arr(5, 0);
        for (auto c : temp) {
            if (c != t) {
                t = c;
                ++i;
            }
            ++arr[i];
        }
        std::sort(arr.rbegin(), arr.rend());
        if (arr[0] == 5)        type = handType::Five;
        else if (arr[0] == 4)   type = handType::Four;
        else if (arr[0] == 3)
            if (arr[1] == 2)    type = handType::FHouse;
            else                type = handType::Three;
        else if (arr[0] == 2)
            if (arr[1] == 2)    type = handType::TPair;
            else                type = handType::Pair;
        else                    type = handType::High;
    }

    bool operator< (const Hand& h) {
        if (type != h.type)
            return type < h.type;
        for (int16_t i = 0; i < 5; ++i) {
            if (cards[i] == h.cards[i])
                continue;
            return Cards[cards[i]] < Cards[h.cards[i]];
        }
        return false;
    }

    std::string cards;
    int bid;
    handType type;
};

struct HandJ : Hand {
    HandJ(std::string c, int b) : Hand(c, b) {
        jokerType = type;
        std::string temp = cards;
        int jc = 0;
        for (auto c : temp)
            if (c == 'J')
                ++jc;
        if (!jc) return;
        std::sort(temp.begin(), temp.end(), [](char a, char b) {
            return Cards[checkJoker(a)] < Cards[checkJoker(b)];
        });
        char t = temp[0];
        int i = 0, ji;
        std::vector<int> arr(5, 0);
        for (auto c : temp) {
            if (c != t) {
                t = c;
                ++i;
            }
            ++arr[i];
        }
        arr[0] = 0;
        std::sort(arr.rbegin(), arr.rend());
        arr[0] += jc;
        if (arr[0] == 5)        jokerType = handType::Five;
        else if (arr[0] == 4)   jokerType = handType::Four;
        else if (arr[0] == 3)
            if (arr[1] == 2)    jokerType = handType::FHouse;
            else                jokerType = handType::Three;
        else if (arr[0] == 2)
            if (arr[1] == 2)    jokerType = handType::TPair;
            else                jokerType = handType::Pair;
        else                    jokerType = handType::High;
    }

    HandJ(const Hand& h) : HandJ(h.cards, h.bid) {}

    bool operator < (const HandJ& h) {
        if (jokerType != h.jokerType)
            return jokerType < h.jokerType;
        for (int16_t i = 0; i < 5; ++i) {
            if (cards[i] == h.cards[i])
                continue;
            return Cards[checkJoker(cards[i])] < Cards[checkJoker(h.cards[i])];
        }
        return false;
    }

    inline static char checkJoker(char c) {
        return c == 'J' ? 'j' : c;
    }

    handType jokerType;
};

std::vector<Hand> parseHands(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::vector<Hand> hands;
    while (!fin.eof()) {
        std::string cards;
        int bid;
        fin >> cards >> bid;
        hands.push_back(Hand(cards, bid));
    }
    return hands;
}

int64_t part1(std::vector<Hand> hands) {
    std::sort(hands.begin(), hands.end());
    int64_t ans = 0;
    for (int16_t i = 0; i < hands.size(); ++i)
        ans += (i + 1) * hands[i].bid;
    return ans;
}

int64_t part2(std::vector<HandJ> hands) {
    std::sort(hands.begin(), hands.end());
    int64_t ans = 0;
    for (int16_t i = 0; i < hands.size(); ++i)
        ans += (i + 1) * hands[i].bid;
    return ans;
}

int main(){
    std::string path = "/root/AdventOfCode2023/day7/test.txt";
    auto hands = parseHands(path);
    std::vector<HandJ> handsJ;
    for (auto h : hands)
        handsJ.push_back(HandJ(h));
    auto a = part1(hands);
    auto b = part2(handsJ);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    return 0;
}
