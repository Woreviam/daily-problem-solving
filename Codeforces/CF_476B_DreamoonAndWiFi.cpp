#include <iomanip>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>

class ProbabilityChecker {

private:
    std::string m_original, m_copy;
    int m_target_coordinate;

    void computeCoordinate() {
        m_target_coordinate  = 0;
        for (auto& c: m_original) {
            if (c == '+')m_target_coordinate++;
            else m_target_coordinate--;
        }
    }
    double computeProbability(int pos, int coordinate) {

        if (pos == m_copy.size())return coordinate == m_target_coordinate;
        if (m_copy[pos] == '+')return computeProbability(pos + 1, coordinate + 1);
        else if (m_copy[pos] == '-') return computeProbability(pos + 1, coordinate - 1);
        else return 0.5 * computeProbability(pos + 1, coordinate + 1) + 0.5 * computeProbability(pos + 1, coordinate - 1);
    }

public:
    ProbabilityChecker() = delete;
    ProbabilityChecker(std::string original, std::string copy)
        : m_original(std::move(original)),
          m_copy(std::move(copy)),
          m_target_coordinate(0)
    {}

    double solve() {
        computeCoordinate();
        return computeProbability(0, 0);
    }
};

#ifndef ONLINE_JUDGE
struct FastIO {
    FastIO() {
        std::freopen("../in.txt", "r", stdin);
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
} fast_io_setup;
#endif

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        ProbabilityChecker P(s1, s2);
        std::cout << std::fixed << std::setprecision(9) << P.solve() << std::endl;
    }

    return 0;

    constexpr double EPSILON = 1e-9;

    //UNIT TEST

    // GROUP 1: CORNER CASES
    // T1: Corner case - one character
    {
        std::string original = "+";
        std::string copy = "?";
        ProbabilityChecker P(original, copy);
        constexpr double expected = 0.5;
        if (std::fabs(P.solve() - expected) < EPSILON) std::cout << "T1 passed" << std::endl;
        else std::cout << "T1 failed" << std::endl;

    }
    // T2: Corner case - one character
    {
        std::string original = "++++++++++";
        std::string copy = "?----?????";
        ProbabilityChecker P(original, copy);
        constexpr double expected = 0;
        if (std::fabs(P.solve() - expected) < EPSILON) std::cout << "T2 passed" << std::endl;
        else std::cout << "T2 failed" << std::endl;
    }
    //GROUP2: SMALL CASES
    // T3: Small case 1
    {
        std::string original = "++-+-";
        std::string copy = "+-+-+";
        ProbabilityChecker P(original, copy);
        constexpr double expected = 1.0;
        if (std::fabs(P.solve() - expected) < EPSILON) std::cout << "T3 passed" << std::endl;
        else std::cout << "T3 failed" << std::endl;
    }
    // T4: Small case 2
    {
        std::string original = "+-+-";
        std::string copy = "+-??";
        ProbabilityChecker P(original, copy);
        constexpr double expected = 0.5;
        if (std::fabs(P.solve() - expected) < EPSILON) std::cout << "T4 passed" << std::endl;
        else std::cout << "T4 failed" << std::endl;
    }
}