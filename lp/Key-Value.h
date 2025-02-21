#ifndef KEY_VALUE_H
#define KEY_VALUE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

struct GameInfo {
    std::string title, date_release, rating;
    bool win, mac, linux, steam_deck;
    int positive_ratio, user_reviews;
    float price_final, price_original, discount;
};

struct User {
    std::string products, reviews;
};

struct Recommendations {
    std::string app_id, date, user_id;
    int helpful, funny;
    bool is_recommended;
    float hours;
};

extern std::unordered_map<std::string, GameInfo> gamesDB;
extern std::unordered_map<std::string, User> usersDB;
extern std::unordered_map<std::string, Recommendations> recommendationsDB;

void LoadGamesDB();
void SaveGamesDBBinary();
bool LoadGamesDBBinary();

void LoadUsersDB();
void SaveUsersDBBinary();
bool LoadUsersDBBinary();

void LoadRecommendationsDB();
void SaveRecommendationsDBBinary();
bool LoadRecommendationsDBBinary();

#endif 
