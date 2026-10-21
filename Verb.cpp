#include "Verb.h"
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

// Приводим в нижний регист
string toLower(string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                    [](unsigned char c){ return tolower(c); });
    return str;
}
// Удаляем пробелы
string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
Verb::Verb(string v1, string v2, string v3, string translation) 
    : v1(move(v1)), v2(move(v2)), v3(move(v3)), translation(move(translation)) {}

const string& Verb::getV1() const
{
    return v1;
}
const string& Verb::getV2() const
{
    return v2;
}
const string& Verb::getV3() const
{
    return v3;
}
const string& Verb::getTranslation() const
{
    return translation;
}

// Нормализуем строки: убираем пробелы и приводим к нижнему регистру
string Verb::normalizedString(const string& str) const
{
    return toLower(trim(str));
}
bool Verb::checkV2(const string& userAnswer) const
{
    string normalizedUser = normalizedString(userAnswer);
    string normalizedCorrect = normalizedString(v2);

    // Поддержка альтернативных форм ("learnt/learned")
    if (normalizedCorrect.find('/') != string::npos)
    {
        size_t slashPos = normalizedCorrect.find('/');
        string form1 = normalizedCorrect.substr(0, slashPos);
        string form2 = normalizedCorrect.substr(slashPos + 1);
        return normalizedUser == form1 || normalizedUser == form2;
    }

    return normalizedUser == normalizedCorrect;
}
bool Verb::checkV3(const string& userAnswer) const
{
    string normalizedUser = normalizedString(userAnswer);
    string normalizedCorrect = normalizedString(v3);

    // Поддержка альтернативных форм
    if (normalizedCorrect.find('/') != string::npos)
    {
        size_t slashPos = normalizedCorrect.find('/');
        string form1 = normalizedCorrect.substr(0, slashPos);
        string form2 = normalizedCorrect.substr(slashPos + 1);
        return normalizedUser == form1 || normalizedUser == form2;
    }

    return normalizedUser == normalizedCorrect;
}