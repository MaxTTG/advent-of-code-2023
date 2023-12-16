#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <thread>

class Beam{
public:
    Beam(int xx, int yy, int vxx, int vyy) : x(xx), y(yy), vx(vxx), vy(vyy) {}
    void move() {
        x += vx;
        y += vy;
    }
    
    std::pair<Beam, Beam> helloSplitter() {
        if (vx)
            return std::make_pair(
                Beam(x, y, 0, 1),
                Beam(x, y, 0, -1)
            );
        return std::make_pair(
            Beam(x, y, 1, 0),
            Beam(x, y, -1, 0)
        );
    }

    void reflect(char ch) {
        std::swap(vx, vy);
        if (ch == '/') {
            vx *= -1;
            vy *= -1;
        }
    }

    int getX() {return x;}
    int getY() {return y;}
    int getVX() {return vx;}
    int getVY() {return vy;}

    bool operator< (const Beam& a) const {
        if (x == a.x) {
            if (y == a.y) {
                if (vx == a.vx) {
                    if (vy == a.vy) {
                        return false;
                    } else return vy < a.vy;
                } else return vx < a.vx;
            } else return y < a.y;
        } else return x < a.x;
    }

private:
    int x;
    int y;
    int vx;
    int vy;
};

std::vector<std::string> parseInput(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(\n";
        throw 1;
    }
    std::vector<std::string> input;
    for (std::string str; std::getline(fin, str);)
        input.push_back(str);
    fin.close();
    return input;
}

int part1(const std::vector<std::string>& input, int xx = 0, int yy = -1, int vx = 0, int vy = 1) {
    std::queue<Beam> beams;
    std::set<Beam> allbeams;
    beams.push(Beam(xx, yy, vx, vy));
    while (!beams.empty()) {
        auto beam = beams.front();
        beams.pop();
        beam.move();
        int x = beam.getX(), y = beam.getY();
        if (x < 0 || x >= input.size() || y < 0 || y >= input[0].size())
            continue;
        char ch = input[x][y];
        if (ch == '.' || (ch == '-' && beam.getVX() == 0) || (ch == '|' && beam.getVY() == 0)) {
            if (allbeams.find(beam) == allbeams.end()) {
                allbeams.insert(beam);
                beams.push(beam);
            }
        } else if (ch == '/' || ch == '\\') {
            beam.reflect(ch);
            if (allbeams.find(beam) == allbeams.end()) {
                allbeams.insert(beam);
                beams.push(beam);
            }
        } else {
            auto [b1, b2] = beam.helloSplitter();
            if (allbeams.find(b1) == allbeams.end()) {
                allbeams.insert(b1);
                beams.push(b1);
            }
            if (allbeams.find(b2) == allbeams.end()) {
                allbeams.insert(b2);
                beams.push(b2);
            }
        }
    }
    std::set<std::pair<int, int>> cells;
    for (auto b : allbeams)
        cells.emplace(b.getX(), b.getY());
    return cells.size();
}

int part2(const std::vector<std::string>& input) {
    std::vector<std::thread> threads;
    std::vector<int> localans(4, 0);
    // top
    threads.emplace_back(
        [&]() {
            for (int i = 0; i < input[0].size(); ++i)
                localans[0] = std::max(localans[0], part1(input, -1, i, 1, 0));
        }
    );
    // right
    threads.emplace_back(
        [&]() {
            for (int i = 0; i < input.size(); ++i)
                localans[1] = std::max(localans[1], part1(input, i, input[0].size(), 0, -1));
        }
    );
    // bot
    threads.emplace_back(
        [&]() {
            for (int i = 0; i < input[0].size(); ++i)
                localans[2] = std::max(localans[2], part1(input, input.size(), i, -1, 0));
        }
    );
    // left
    threads.emplace_back(
        [&]() {
            for (int i = 0; i < input[0].size(); ++i)
                localans[3] = std::max(localans[3], part1(input, i, -1, 0, 1));
        }
    );

    for (auto& thread : threads)
        thread.join();

    int ans = 0;
    for (auto a : localans)
        ans = std::max(ans, a);
    
    return ans;
}

int main() {
    std::string path("../input.txt");
    auto input = parseInput(path);
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
}
// 6855
// 7513