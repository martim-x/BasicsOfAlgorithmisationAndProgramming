#include <bits/stdc++.h>
using namespace std;


int OverRidestrlen(char str[]) {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}


bool OverRidestrcmp(char str1[], char str2[]) {
    int i = 0;
    if (OverRidestrlen(str1) != OverRidestrlen(str2))
        return false;

    while (str1[i] != '\0') {
        if (str1[i] != str2[2])
            return false;
        i++;
    }

    return true;
}

// OVERDRIVE!!!
// void OverRidestrcpy(char* dest[], char* src[]) {
//     int i = 0;
//     while (src[i] != '\0') {
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
// }


// void OverRidestrcpy(const char* dest[],const char* src[]) {
//     int i = 0;
//     while (src[i] != '\0') {
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
// }


void OverRidestrcpy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}



// vector<const char*> OverRidestrtok(const char* str[],const  char* tokens[]) {
//     int i = 0, j = 0;
//     vector<const char*> tokenedVec;
//     int pointerToken = 0;

//     const char* strSave[OverRidestrlen(str) + 1];
//     OverRidestrcpy(strSave, str);

//     while (str[i] != '\0') {
//         j = 0;
//         while (tokens[j] != '\0') {
//             if (str[i] == tokens[j]) {
//                 str[i] = '\0';
//                 tokenedVec.push_back(&str[pointerToken]);
//                 pointerToken = i + 1;
//                 break;
//             }
//             j++;
//         }
//         i++;
//     }

//     if (pointerToken < i)
//         tokenedVec.push_back(&str[pointerToken]);

//     OverRidestrcpy(str, strSave);

//     return tokenedVec;

// }



// vector<const char*> OverRidestrtok(char str[], char tokens[]) {
//     int i = 0, j = 0;
//     vector<const char*> tokenedVec;
//     int pointerToken = 0;

//     const char* strSave[OverRidestrlen(str) + 1];
//     OverRidestrcpy(strSave, str);

//     while (str[i] != '\0') {
//         j = 0;
//         while (tokens[j] != '\0') {
//             if (str[i] == tokens[j]) {
//                 str[i] = '\0';
//                 tokenedVec.push_back(&str[pointerToken]);
//                 pointerToken = i + 1;
//                 break;
//             }
//             j++;
//         }
//         i++;
//     }

//     if (pointerToken < i)
//         tokenedVec.push_back(&str[pointerToken]);

//     OverRidestrcpy(str, strSave);

//     return tokenedVec;

// }


vector<char*> OverRidestrtok(char str[], char tokens[]) {
    int i = 0, j = 0;
    vector<char*> tokenedVec;
    int pointerToken = 0;

    char strSave[OverRidestrlen(str) + 1];
    OverRidestrcpy(strSave, str);

    while (str[i] != '\0') {
        j = 0;
        while (tokens[j] != '\0') {
            if (str[i] == tokens[j]) {
                str[i] = '\0';
                tokenedVec.push_back(&str[pointerToken]);
                pointerToken = i + 1;
                break;
            }
            j++;
        }
        i++;
    }

    if (pointerToken < i)
        tokenedVec.push_back(&str[pointerToken]);

    OverRidestrcpy(str, strSave);

    return tokenedVec;

}


void OverRidestrev(char word[]) {
    int leghtStr = OverRidestrlen(word);
    char wordBuf[leghtStr];
    OverRidestrcpy(wordBuf, word);
    int i = 0;
    while (i <= leghtStr) {
        word[i] = wordBuf[leghtStr - i];
        i++;
    }
}


void task4() {

    char s1[] = "asdfghjkksfddsaf\0";
    char s2[] = "asdghhjhgfjkdasa\0";
    char c1, c2;
    int lenS1 = OverRidestrlen(s1);
    for (int i = 0; i < lenS1; i++) {
        c1 = s1[i];
        c2 = s2[i];
        if (c2 == c1)
            cout << "c2 equals c1        -- " << "c2: " << c2 << ", c1: " << c1 << endl;
        else
            cout << "c2 doesm't equal c1 -- " << "c2: " << c2 << ", c1: " << c1 << endl;
    }

    char s3[] = "001 11010 10101010 10101 110101 101010101010 10101010\0";
    char c3;
    set<int> symbols;
    int buffer = 0;
    int lenS3 = OverRidestrlen(s3);
    for (int i = 0; i < lenS3; i++) {
        c3 = s3[i];
        if (c3 == ' ' || i == lenS3) {
            symbols.insert(buffer);
            buffer = 0;
        }
        buffer++;
    }

    cout << "max symbols: " << *(--symbols.end()) << endl;
}


void task5_1() {
    char str[] = "The Ugly Duckling is one of the most beloved English stories of all time.\n"
        "The story follows the journey of an ugly duckling who is rejected by his family and friends.\n"
        "He eventually learns to love himself for who he is and finds happiness in his new life.\n"
        "The story is popular with English learners because it teaches valuable lessons about self-acceptance and diversity.\n"
        "In addition, the story is written in simple, easy-to-understand English, making it an ideal choice for beginners.\n"
        "Whether you're just starting to learn English or you’re a seasoned speaker, The Ugly Duckling is a great choice for anyone looking to improve their English skills.\0";

    cout << "Current string:\n" << str << endl;

    char term[50];
    cout << "Input the terminate: ";
    cin >> term;

    int term_len = OverRidestrlen(term);

    char terminators[] = " .;:\n\0";
    vector<char*> words = OverRidestrtok(str, terminators);

    for (auto word : words) {
        cout << word << endl;
        if (OverRidestrcmp(word + OverRidestrlen(word) - term_len, term))
            cout << word << endl;
    }
}


void task5_4() {
    char str1[] = "The story follows the journey of an ugly duckling who is rejected by his family and friends.";
    char terminators[] = " .;:\n\0";
    vector<char*> words = OverRidestrtok(str1, terminators);
    vector<char*> wordsODD;
    for (int i = 0; i < words.size(); i++)
        if (i % 2)
            wordsODD.push_back(words[i]);

    for (auto i : wordsODD)
        cout << i << " ";
}


void task5_5() {
    char str1[] = "The story follows the journey of an ugly duckling who is rejected by his family and friends.";
    char str2[] = "In of addition, the story is written by in simple, easy-to-understand English, making it an ideal choice for beginners.";

    vector<char*> vecstr1;
    vector<char*> vecstr2;

    char* word1 = strtok(str1, " .,:;\n\0");
    while (word1 != nullptr) {
        vecstr1.push_back(word1);
        word1 = strtok(nullptr, " .,:;\n\0");
    }

    char* word2 = strtok(str2, " .,:;\n\0");
    while (word2 != nullptr) {
        vecstr2.push_back(word2);
        word2 = strtok(nullptr, " .,:;\n\0");
    }

    char* sh_word = vecstr1[0];
    bool flag = false;
    for (auto word1 : vecstr1) {
        if (strlen(sh_word) > strlen(word1) || flag) {
            strcpy(sh_word, word1);
            flag = false;
        }

        for (auto word2 : vecstr2)
        {
            cout << word1 << " " << word2 << endl;
            if (!strcmp(word1, word2)) {
                flag = true;
                break;;
            }
        }

    }
    cout << "shortest word: " << sh_word << endl;
}


int main() {
    // task4();
    task5_1();
    // task5_4();
    // task5_5();
    return 0;
}