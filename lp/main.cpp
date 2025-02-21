#include <iostream>
#include "key-value.h"

void PrintGamesDB() {
    std::cout << "\n--- Juegos Cargados ---\n";
    int count = 0;
    for (const auto& [app_id, game] : gamesDB) {
        std::cout << "ID: " << app_id 
                  << ", Título: " << game.title 
                  << ", Fecha: " << game.date_release 
                  << ", Rating: " << game.rating 
                  << ", Windows: " << game.win
                  << ", Mac: " << game.mac
                  << ", Linux: " << game.linux
                  << ", Steam Deck: " << game.steam_deck
                  << ", Precio Final: " << game.price_final 
                  << ", Precio Original: " << game.price_original 
                  << ", Descuento: " << game.discount 
                  << ", Reseñas: " << game.user_reviews 
                  << "\n";
        if (++count == 5) break;
    }
}

void PrintUsersDB() {
    std::cout << "\n--- Usuarios Cargados ---\n";
    int count = 0;
    for (const auto& [user_id, user] : usersDB) {
        std::cout << "ID Usuario: " << user_id 
                  << ", Productos: " << user.products 
                  << ", Reseñas: " << user.reviews << "\n";
        if (++count == 5) break;
    }
}

void PrintRecommendationsDB() {
    std::cout << "\n--- Recomendaciones Cargadas ---\n";
    int count = 0;
    for (const auto& [review_id, rec] : recommendationsDB) {
        std::cout << "ID Reseña: " << review_id
                  << ", App ID: " << rec.app_id
                  << ", Usuario: " << rec.user_id
                  << ", Fecha: " << rec.date
                  << ", Útil: " << rec.helpful
                  << ", Divertida: " << rec.funny
                  << ", Recomendada: " << (rec.is_recommended ? "Sí" : "No")
                  << ", Horas Jugadas: " << rec.hours << "\n";
        if (++count == 5) break;
    }
}

int main() {
    // Cargar desde CSV o binario
    LoadGamesDB();
    LoadUsersDB();
    LoadRecommendationsDB();

    // Guardar en binario (para futuras ejecuciones)
    SaveGamesDBBinary();
    SaveUsersDBBinary();
    SaveRecommendationsDBBinary();

    // Cargar desde binario para verificar
    std::cout << "Cargando desde binario para verificar...\n";
    LoadGamesDBBinary();
    LoadUsersDBBinary();
    LoadRecommendationsDBBinary();

    // Imprimir los primeros 5 registros de cada base de datos
    PrintGamesDB();
    PrintUsersDB();
    PrintRecommendationsDB();

    return 0;
}
