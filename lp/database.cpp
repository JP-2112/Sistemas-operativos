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

std::unordered_map<std::string, GameInfo> gamesDB;
std::unordered_map<std::string, User> usersDB;
std::unordered_map<std::string, Recommendations> recommendationsDB;

void SaveGamesDBBinary() {
    std::ofstream outfile("games.dat", std::ios::binary);
    size_t size = gamesDB.size();
    outfile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& [app_id, game] : gamesDB) {
        size_t len = app_id.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(app_id.data(), len);
        len = game.title.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(game.title.data(), len);
        len = game.date_release.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(game.date_release.data(), len);
        len = game.rating.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(game.rating.data(), len);
        outfile.write(reinterpret_cast<const char*>(&game.win), sizeof(game.win));
        outfile.write(reinterpret_cast<const char*>(&game.mac), sizeof(game.mac));
        outfile.write(reinterpret_cast<const char*>(&game.linux), sizeof(game.linux));
        outfile.write(reinterpret_cast<const char*>(&game.steam_deck), sizeof(game.steam_deck));
        outfile.write(reinterpret_cast<const char*>(&game.positive_ratio), sizeof(game.positive_ratio));
        outfile.write(reinterpret_cast<const char*>(&game.user_reviews), sizeof(game.user_reviews));
        outfile.write(reinterpret_cast<const char*>(&game.price_final), sizeof(game.price_final));
        outfile.write(reinterpret_cast<const char*>(&game.price_original), sizeof(game.price_original));
        outfile.write(reinterpret_cast<const char*>(&game.discount), sizeof(game.discount));
    }
}

bool LoadGamesDBBinary() {
    std::ifstream infile("games.dat", std::ios::binary);
    if (!infile) return false;
    size_t size;
    infile.read(reinterpret_cast<char*>(&size), sizeof(size));
    gamesDB.clear();
    for (size_t i = 0; i < size; i++) {
        std::string app_id, title, date_release, rating;
        bool win, mac, linux, steam_deck;
        int positive_ratio, user_reviews;
        float price_final, price_original, discount;
        size_t len;
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        app_id.resize(len);
        infile.read(app_id.data(), len);
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        title.resize(len);
        infile.read(title.data(), len);
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        date_release.resize(len);
        infile.read(date_release.data(), len);
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        rating.resize(len);
        infile.read(rating.data(), len);
        infile.read(reinterpret_cast<char*>(&win), sizeof(win));
        infile.read(reinterpret_cast<char*>(&mac), sizeof(mac));
        infile.read(reinterpret_cast<char*>(&linux), sizeof(linux));
        infile.read(reinterpret_cast<char*>(&steam_deck), sizeof(steam_deck));
        infile.read(reinterpret_cast<char*>(&positive_ratio), sizeof(positive_ratio));
        infile.read(reinterpret_cast<char*>(&user_reviews), sizeof(user_reviews));
        infile.read(reinterpret_cast<char*>(&price_final), sizeof(price_final));
        infile.read(reinterpret_cast<char*>(&price_original), sizeof(price_original));
        infile.read(reinterpret_cast<char*>(&discount), sizeof(discount));
        gamesDB[app_id] = {title, date_release, rating, win, mac, linux, steam_deck, positive_ratio, user_reviews, price_final, price_original, discount};
    }
    return true;
}

void LoadGamesDB() {
    if (LoadGamesDBBinary()) {
        std::cout << "Datos de juegos cargados desde binario.\n";
        return;
    }
    std::ifstream infile("games.csv");
    if (!infile.is_open()) {
        std::cout << "Error al abrir el archivo games.csv\n";
        return;
    }
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line)) {
        std::istringstream flow(line);
        std::string app_id, aux;
        GameInfo game;
        std::getline(flow, app_id, ',');
        std::getline(flow, game.title, ',');
        std::getline(flow, game.date_release, ',');
        std::getline(flow, game.rating, ',');
        std::getline(flow, aux, ','); game.win = (aux == "true");
        std::getline(flow, aux, ','); game.mac = (aux == "true");
        std::getline(flow, aux, ','); game.linux = (aux == "true");
        std::getline(flow, aux, ','); game.steam_deck = (aux == "true");
        std::getline(flow, aux, ','); game.positive_ratio = std::stoi(aux);
        std::getline(flow, aux, ','); game.user_reviews = std::stoi(aux);
        std::getline(flow, aux, ','); game.price_final = std::stof(aux);
        std::getline(flow, aux, ','); game.price_original = std::stof(aux);
        std::getline(flow, aux, ','); game.discount = std::stof(aux);
        gamesDB[app_id] = game;
    }
    infile.close();
        SaveGamesDBBinary();
    }

void SaveUsersDBBinary() {
    std::ofstream outfile("users.dat", std::ios::binary);
    size_t size = usersDB.size();
    outfile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& [user_id, user] : usersDB) {
        size_t len = user_id.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(user_id.data(), len);
        len = user.products.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(user.products.data(), len);
        len = user.reviews.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(user.reviews.data(), len);
    }
}

bool LoadUsersDBBinary() {
    std::ifstream infile("users.dat", std::ios::binary);
    if (!infile) return false;
    size_t size;
    infile.read(reinterpret_cast<char*>(&size), sizeof(size));
    usersDB.clear();
    for (size_t i = 0; i < size; i++) {
        std::string user_id, products, reviews;
        size_t len;
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        user_id.resize(len);
        infile.read(user_id.data(), len);
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        products.resize(len);
        infile.read(products.data(), len);
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        reviews.resize(len);
        infile.read(reviews.data(), len);
        usersDB[user_id] = {products, reviews};
    }
    return true;
}

void LoadUsersDB() {
    if (LoadUsersDBBinary()) {
        std::cout << "Datos de usuarios cargados desde binario.\n";
        return;
    }
    std::ifstream infile("users.csv");
    if (!infile.is_open()) {
        std::cout << "Error al abrir el archivo users.csv\n";
        return;
    }
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line)) {
        std::istringstream flow(line);
        std::string user_id;
        User user;
        std::getline(flow, user_id, ',');
        std::getline(flow, user.products, ',');
        std::getline(flow, user.reviews, ',');
        usersDB[user_id] = user;
    }
    infile.close();
    SaveUsersDBBinary();
}

void SaveRecommendationsDBBinary() {
    std::ofstream outfile("recommendations.dat", std::ios::binary);
    size_t size = recommendationsDB.size();
    outfile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& [review_id, rec] : recommendationsDB) {
        size_t len = review_id.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(review_id.data(), len);
        len = rec.app_id.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(rec.app_id.data(), len);
        outfile.write(reinterpret_cast<const char*>(&rec.helpful), sizeof(rec.helpful));
        outfile.write(reinterpret_cast<const char*>(&rec.funny), sizeof(rec.funny));
        len = rec.date.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(rec.date.data(), len);
        outfile.write(reinterpret_cast<const char*>(&rec.is_recommended), sizeof(rec.is_recommended));
        outfile.write(reinterpret_cast<const char*>(&rec.hours), sizeof(rec.hours));
        len = rec.user_id.size();
        outfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outfile.write(rec.user_id.data(), len);
    }
}

bool LoadRecommendationsDBBinary() {
    std::ifstream infile("recommendations.dat", std::ios::binary);
    if (!infile) return false;
    size_t size;
    infile.read(reinterpret_cast<char*>(&size), sizeof(size));
    recommendationsDB.clear();
    for (size_t i = 0; i < size; i++) {
        std::string review_id, app_id, date, user_id;
        int helpful, funny;
        bool is_recommended;
        float hours;
        size_t len;
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        review_id.resize(len);
        infile.read(review_id.data(), len);
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        app_id.resize(len);
        infile.read(app_id.data(), len);
        infile.read(reinterpret_cast<char*>(&helpful), sizeof(helpful));
        infile.read(reinterpret_cast<char*>(&funny), sizeof(funny));
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        date.resize(len);
        infile.read(date.data(), len);
        infile.read(reinterpret_cast<char*>(&is_recommended), sizeof(is_recommended));
        infile.read(reinterpret_cast<char*>(&hours), sizeof(hours));
        infile.read(reinterpret_cast<char*>(&len), sizeof(len));
        user_id.resize(len);
        infile.read(user_id.data(), len);
        recommendationsDB[review_id] = {app_id, date, user_id, helpful, funny, is_recommended, hours};
    }
    return true;
}

void LoadRecommendationsDB() {
    if (LoadRecommendationsDBBinary()) {
        std::cout << "Datos de recomendaciones cargados desde binario.\n";
        return;
    }
    std::ifstream infile("recommendations.csv");
    if (!infile.is_open()) {
        std::cout << "Error al abrir el archivo recommendations.csv\n";
        return;
    }
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line)) {
        std::istringstream flow(line);
        std::string review_id, aux;
        Recommendations rec;
        std::getline(flow, review_id, ',');
        std::getline(flow, rec.app_id, ',');
        std::getline(flow, aux, ','); rec.helpful = std::stoi(aux);
        std::getline(flow, aux, ','); rec.funny = std::stoi(aux);
        std::getline(flow, rec.date, ',');
        std::getline(flow, aux, ','); rec.is_recommended = (aux == "true");
        std::getline(flow, aux, ','); rec.hours = std::stof(aux);
        std::getline(flow, rec.user_id, ',');
        recommendationsDB[review_id] = rec;
    }
    infile.close();
    SaveRecommendationsDBBinary();
}
