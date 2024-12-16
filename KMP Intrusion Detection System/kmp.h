#ifndef KMP_H
#define KMP_H

#include <vector>
#include <string>

class KMP {
    public:
    KMP(const std::string& pattern);

    std::vector<int> search(const std::string& text);

    private:
    std::string pattern;
    std::vector<int> lps;

    void buildLPS();
};

#endif