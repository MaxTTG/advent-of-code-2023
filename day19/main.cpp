#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <list>
#include <array>
#include <numeric>
#include <tuple>
#include <queue>

std::map<char, int> categories{{'x', 0}, {'m', 1}, {'a', 2}, {'s', 3}};

typedef std::array<int, 4> Detail;
typedef std::array<std::pair<int, int>, 4> DRange;

struct Rule {
    Rule() = default;
    Rule(char cat, char comp, int cond, std::string t) : category(cat), condition(cond), then(t) { less = (comp == '<'); }
    Rule(const Rule& rule) {
        category = rule.category;
        less = rule.less;
        condition = rule.condition;
        then = rule.then;
    }

    Rule& operator= (const Rule& rule) {
        category = rule.category;
        less = rule.less;
        condition = rule.condition;
        then = rule.then;
        return *this;
    }

    bool check_detail(const Detail& d) {
        if (less) return d[categories[category]] < condition;
        return d[categories[category]] > condition;
    }

    std::tuple<DRange, std::string, DRange> check_range(DRange& dr) {
        DRange yes = dr, no = dr;
        int i = categories[category];
        if (less) { // if <
            yes[i].second = condition - 1;
            no[i].first = condition;
        } else { // if >
            yes[i].first = condition + 1;
            no[i].second = condition;
        }
        return {yes, then, no};
    }

    char category;
    bool less;
    int condition;
    std::string then;
};

struct Workflow {
    Workflow() = default;
    Workflow(const std::string& d) : default_(d) {}
    Workflow(const Workflow& wf) : default_(wf.default_) { rules = wf.rules; }

    Workflow& operator= (const Workflow& wf) {
        rules = wf.rules;
        default_ = wf.default_;
        return *this;
    }

    void push_back_rule(const Rule& rule) {rules.push_back(rule);}

    std::string check_detail(const Detail& d) {
        for (auto& rule : rules)
            if (rule.check_detail(d))
                return rule.then;
        return default_;
    }

    std::vector<std::pair<std::string, DRange>> check_range(const DRange& range) {
        std::vector<std::pair<std::string, DRange>> ranges;
        auto r = range;
        for (auto& rule : rules) {
            auto [yes, str, no] = rule.check_range(r);
            ranges.push_back({str, yes});
            r = no;
        }
        ranges.push_back({default_, r});
        return ranges;
    }

    std::vector<Rule> rules;
    std::string default_;
};

std::pair<std::map<std::string, Workflow>, std::vector<Detail>> parseInput(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(\n";
        throw 1;
    }
    std::regex pattern_wf_name_default("([a-z]+)\\{.*,([A-Za-z]+)\\}");
    std::regex pattern_wf_rule("([xmas])(<|>)(\\d+):([A-Za-z]+)");
    std::regex pattern_dt("x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)");
    
    std::map<std::string, Workflow> wfs;
    std::vector<Detail> dts;

    // workflows
    for (std::string str; std::getline(fin, str);) {
        if (str.empty()) break;
        std::smatch match;
        std::regex_search(str, match, pattern_wf_name_default);
        std::string name = match[1].str();
        Workflow wf(match[2].str());
        while (std::regex_search(str, match, pattern_wf_rule)) {
            wf.push_back_rule(Rule(match[1].str()[0], match[2].str()[0], std::stoi(match[3].str()), match[4]));
            str = match.suffix();
        }
        wfs.insert({name, wf});
    }
    // details
    for (std::string str; std::getline(fin, str);) {
        std::smatch match;
        std::regex_search(str, match, pattern_dt);
        dts.push_back({std::stoi(match[1].str()), std::stoi(match[2].str()), std::stoi(match[3].str()), std::stoi(match[4].str())});
    }

    fin.close();
    return std::make_pair(wfs, dts);
}

int part1(std::map<std::string, Workflow>& wfs, std::vector<Detail>& dts) {
    int ans = 0;
    for (auto& d : dts) {
        std::string key = "in";
        while (key != "A" && key != "R")
            key = wfs[key].check_detail(d);
        if (key == "A") 
            ans += std::accumulate(d.begin(), d.end(), 0);
    }
    return ans;
}

long long part2(std::map<std::string, Workflow>& wfs) {
    long long ans = 0;
    std::list<DRange> amarked;
    std::queue<std::pair<std::string, DRange>> ranges;
    ranges.push({"in", {{{1, 4000}, {1, 4000}, {1,4000}, {1,4000}}}});
    while (!ranges.empty()) {
        auto [path, range] = ranges.front(); ranges.pop();
        auto vec = wfs[path].check_range(range);
        for (auto& v : vec) {
            if (v.first == "A")
                amarked.push_back(v.second);
            else if (v.first != "R")
                ranges.push(v);
        }
    }
    for (auto& range : amarked) {
        long long temp = 1;
        for (auto& c : range)
            temp *= (c.second - c.first + 1);
        ans += temp;
    }
    return ans;
}

int main() {
    std::string path("../input.txt");
    auto [wf, dt] = parseInput(path);
    std::cout << part1(wf, dt) << std::endl;
    std::cout << part2(wf) << std::endl;
}
// 
// 