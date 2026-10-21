#pragma once

#include "Verb.h"
#include <vector>
#include <random>
#include <string>

using namespace std;

class Trainer
{
    private:
        vector<Verb> verbs;
        int score;
        int totalQuestions;
        mt19937 gen;
        
        void initRandom();
        void loadVerbsFromFile(const string& filename);
        void loadDefaultVerbs();
        void showResults() const;
        void saveStats() const;
    public:
        Trainer();
        void startQuiz(int qCount);
};