#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>

int inputValidatedInt(const std::string& prompt, int min = INT32_MIN, int max = INT32_MAX);
double inputValidatedDouble(const std::string& prompt, double min = INT32_MIN, double max = INT32_MAX);
std::string inputValidatedString(const std::string& prompt, const std::string& allowedChars, bool canBeEmpty, const std::string& strReplaced = "EMPTY");
std::string inputValidatedName(const std::string& prompt, bool canBeEmpty = false);
std::string inputTime(const std::string& promt);
std::string inputValidatedCountryOrTownName(const std::string& promt, bool canBeEmpty = false);
std::string inputValidatedPhoneNumber(const std::string& prompt);
bool isValidName(const std::string& name);
bool isValidCountryOrTownName(const std::string& name);
#endif