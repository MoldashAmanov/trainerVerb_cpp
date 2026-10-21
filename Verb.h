#pragma once
#include <string>

using namespace std;

class Verb
{
    private:
        string v1;
        string v2;
        string v3;
        string translation;
        string normalizedString(const string& str) const;
    public:
        Verb(string v1, string v2, string v3, string translation);
        const string& getV1() const;
        const string& getV2() const;
        const string& getV3() const;
        const string& getTranslation() const;

        bool checkV2(const string& userAnswer) const;
        bool checkV3(const string& userAnswer) const;
};
