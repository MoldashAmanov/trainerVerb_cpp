#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Trainer::initRandom()
{
    random_device rd;
    gen = mt19937(rd());
}
void Trainer::loadVerbsFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не удалось открыть файл " << filename << ". Загрузка встроенной базы.\n";
        loadDefaultVerbs();
        return;
    }
    string line;
    int loadedCount = 0;

    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') // Пропускаем пустые строки и комментарии
            continue;

        stringstream ss(line);
        string v1, v2, v3, translation;

        if (getline(ss, v1, '|') &&
            getline(ss, v2, '|') &&
            getline(ss, v3, '|') &&
            getline(ss, translation))
        {
            verbs.emplace_back(v1, v2, v3, translation);
            loadedCount++;
        }
    }

    file.close();
    cout << "Загружено глаголов из файла: " << loadedCount << "\n";
}
void Trainer::loadDefaultVerbs()
{
    // Запасная база, если основной файл не найден
    verbs.reserve(20);
    verbs.emplace_back("go", "went", "gone", "идти");
    verbs.emplace_back("see", "saw", "seen", "видеть");
    verbs.emplace_back("take", "took", "taken", "брать");
    verbs.emplace_back("write", "wrote", "written", "писать");
    verbs.emplace_back("speak", "spoke", "spoken", "говорить");
    verbs.emplace_back("break", "broke", "broken", "ломать");
    verbs.emplace_back("choose", "chose", "chosen", "выбирать");
    verbs.emplace_back("drive", "drove", "driven", "водить");
    verbs.emplace_back("fly", "flew", "flown", "летать");
    verbs.emplace_back("forget", "forgot", "forgotten", "забывать");
    verbs.emplace_back("drink", "drank", "drunk", "пить");
    verbs.emplace_back("eat", "ate", "eaten", "есть");
    verbs.emplace_back("give", "gave", "given", "давать");
    verbs.emplace_back("know", "knew", "known", "знать");
    verbs.emplace_back("read", "read", "read", "читать");
    verbs.emplace_back("be", "was/were", "been", "быть");
    verbs.emplace_back("have", "had", "had", "иметь");
    verbs.emplace_back("do", "did", "done", "делать");
    verbs.emplace_back("make", "made", "made", "создавать");
    verbs.emplace_back("come", "came", "come", "приходить");
}
void Trainer::showResults() const
{
    cout << "\n------------------------------";
    cout << "----------РЕЗУЛЬТАТЫ------------";
    cout << "--------------------------------\n";
    cout << "Правильных ответов: " << score << " из " << totalQuestions << "\n";
    int percent = (totalQuestions > 0) ? (score * 100 / totalQuestions) : 0;
    cout << "Точность: " << percent << "%\n\n";

    if (percent == 100)
        cout << "Превосходно!!!\n";
    else if (percent >= 70)
        cout << "Хороший результат!\n";
    else 
        cout << "Стоит повторить таблицу глаголов\n";
}
void Trainer::saveStats() const
{
    ofstream file("stats.txt", ios::app);
    if (file.is_open())
    {
        file << "Score: " << score << "/" << totalQuestions << "\n";
        file.close();
    }
}
Trainer::Trainer() : score(0), totalQuestions(0)
{
    initRandom();
    loadVerbsFromFile("verbs.txt");
}
void Trainer::startQuiz(int qCount)
{
    if (verbs.empty())
    {
        cout << "База глаголов пуста!\n";
        return;
    }

    score = 0;
    totalQuestions = qCount;
    uniform_int_distribution<> distrib(0, static_cast<int>(verbs.size() - 1));

    cout << "\n  Начало теста (" << qCount << " вопросов) ---\n";
    cout << "Регистр и пробелы не имеют значения!\n";

    for (int i = 1; i <= qCount; ++i)
    {
        int randomIndex = distrib(gen);
        const Verb& currentVerb = verbs[randomIndex];

        cout << "\n[" << i << "/" << qCount << "] Перевод: " << currentVerb.getTranslation() << " | V1: " << currentVerb.getV1() << "\n";
        
        string userV2, userV3;

        cout << " -> V2 (Past Simple): ";
        getline(cin, userV2);

        cout << " -> V3 (Past Participle): ";
        getline(cin, userV3);

        bool isV2Correct = currentVerb.checkV2(userV2);
        bool isV3Correct = currentVerb.checkV3(userV3);

        if (isV2Correct && isV3Correct)
        {
            cout << "Верно!\n";
            score++;
        }
        else
        {
            cout << "Ошибка!\n";
            cout << "  Правильно: V2 = " << currentVerb.getV2() << ", V3 = " << currentVerb.getV3() << "\n";
        }
    }
    showResults();
    saveStats();
}