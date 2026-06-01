#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cstdio>

class SocialNetwork {

private:
    int m_total_users, m_total_groups;
    std::vector<std::vector<int>>m_groups;
    std::vector<int>m_parent;

    int Find(int u) {
        if (m_parent[u] == u)return u;
        return m_parent[u] = Find(m_parent[u]);
    }

    void Union(int u, int v) {
        if (m_component_size[u] > m_component_size[v])std::swap(u, v);
        m_parent[u] = v;
        m_component_size[v] += m_component_size[u];
    }

public:
    std::vector<int>m_component_size;
    SocialNetwork() = delete;
    SocialNetwork(int total_users, int total_groups, std::vector<std::vector<int>> groups)
        : m_total_users(total_users),
          m_total_groups(total_groups),
          m_groups(std::move(groups))
    {
        m_parent.resize(m_total_users);
        std::iota(m_parent.begin(), m_parent.end(), 0);
        m_component_size.resize(m_total_users, 1);

        for (auto& group: m_groups) {
            for (int i = 1; i < group.size(); i++) {
                int u = Find(group[i - 1]);
                int v = Find(group[i]);
                if (u != v)Union(u, v);
            }
        }

        for (int i = 0; i < m_total_users; i++)
            m_component_size[i] = m_component_size[Find(i)];
    }
    friend std::ostream& operator<<(std::ostream& os, const SocialNetwork& network);
};

std::ostream& operator<<(std::ostream& os, const SocialNetwork& network) {
    for (int i = 0; i < network.m_total_users; i++) {
        os << network.m_component_size[i] << " ";
    }
    return os;
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("../in.txt", "r", stdin);
#endif
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        int total_users, total_groups;
        std::cin >> total_users >> total_groups;
        std::vector<std::vector<int>> groups(total_groups);

        for (int i = 0; i < total_groups; i++) {

            int group_size;
            std::cin >> group_size;
            groups[i].resize(group_size);

            for (int j = 0 ; j < group_size; j++){
                std::cin >> groups[i][j];
                groups[i][j]--;
            }
        }

        SocialNetwork network(total_users, total_groups, groups);
        std::cout << network << std::endl;
    }
#ifndef ONLINE_JUDGE
    // UNIT TEST
    // GROUP 1: CORNER CASES
    // T1: total_users = 1
    {
        constexpr int total_users = 1;
        constexpr int total_groups = 1;
        std::vector<std::vector<int>>groups = {{1, 1}};
        SocialNetwork network(total_users, total_groups, groups);
        std::vector<int>expected = {1};

        if (network.m_component_size != expected) std::cout << "T1 failed" << std::endl;
        else std::cout << "T1 passed" << std::endl;
    }
    // T2: total_users = 10^5 and total_groups = 1
    {
        constexpr int total_users = 100000;
        constexpr int total_groups = 1;

        std::vector<std::vector<int>>groups(total_groups);
        groups[0].resize(total_users);
        std::iota(groups[0].begin(), groups[0].end(), 1);

        SocialNetwork network(total_users, total_groups, groups);
        std::vector<int>expected(total_users, total_users);

        if (network.m_component_size != expected) std::cout << "T2 failed" << std::endl;
        else std::cout << "T2 passed" << std::endl;
    }
#endif
    return 0;
}

