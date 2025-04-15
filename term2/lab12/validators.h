#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>

char inputValidatedChar(const std::string& prompt);
std::string inputValidatedWord(const std::string& prompt);
std::string inputValidatedString(const std::string& prompt);
int inputValidatedInt(const std::string& prompt, int min, int max);
#endif