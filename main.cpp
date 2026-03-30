#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    // Crear la ventana (ancho, alto, título)
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pokemon Battle Simulator");
    
    //Cargar Texturas
    
    sf::Texture backgroundBattle;
    backgroundBattle.loadFromFile("sprite/background.png");
    
    sf::Texture pokemonFront;
    pokemonFront.loadFromFile("sprite/pikachu_front.png");
    
    sf::Texture pokemonBack;
    pokemonBack.loadFromFile("sprite/charmander_back.png");
    
    
    //Texture HUD
    
    sf::Texture enemyBar;
    enemyBar.loadFromFile("sprite/hpenemy.png");
    
    sf::Texture userBar;
    userBar.loadFromFile("sprite/hpbaruser.png");
    
    sf::Texture bar;
    bar.loadFromFile("sprite/bar.png");
    
    
    //Crear Sprites y sus atributos
    
    sf::Sprite backgroundBattle_sprite(backgroundBattle);
    backgroundBattle_sprite.setPosition(0.0f, 0.0f);
    backgroundBattle_sprite.setScale(3.5f, 4.2f);
    
    sf::Sprite pokemonFront_Sprite(pokemonFront); //Pokemon Frontal Sprite
    pokemonFront_Sprite.setPosition(500.0f, 65.0f);
    pokemonFront_Sprite.setScale(4.0f, 4.0f);
    
    sf::Sprite pokemonBack_Sprite(pokemonBack); //Pokemon trasero Sprite
    pokemonBack_Sprite.setPosition(40.0f, 240.0f);
    pokemonBack_Sprite.setScale(4.0f, 4.0f);
    
    //Sprite HUD
    
    sf::Sprite enemyBar_sprite(enemyBar); //Barra enemiga
    enemyBar_sprite.setPosition(30.0f, 30.0f);
    enemyBar_sprite.setScale(4.0f, 4.0f);
    
    sf::Sprite userBar_sprite(userBar); //Bara del player
    userBar_sprite.setPosition(430.0f, 300.0f);
    userBar_sprite.setScale(3.5f, 3.5f);
    
    sf::Sprite bar_sprite(bar);
    bar_sprite.setPosition(0.0f, 453.0f);
    bar_sprite.setScale(3.4f, 3.0f);
    
    //Musica
    
    sf::Music pokemonBattleWild;
    pokemonBattleWild.openFromFile("music/battle.ogg");
    pokemonBattleWild.setLoop(true);
    pokemonBattleWild.play();
    
    // Loop principal de la aplicación
    while (ventana.isOpen()) {
        // Procesar todos los eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            // Si el usuario cierra la ventana
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            
            // Si presiona la tecla ESC
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Escape) {
                    ventana.close();
                }
            }
        }
        
        // Limpiar la ventana con un color
        ventana.clear(sf::Color(50, 100, 150));  // Azul grisáceo
        
        // Aquí irá todo lo que quieras dibujar
        
        // Mejor: agrupar por tipo y comentar claramente
		// CAPA 0: Fondo
		ventana.draw(backgroundBattle_sprite);

		// CAPA 1: Pokémon (los que están detrás de la interfaz)
		ventana.draw(pokemonBack_Sprite);
		ventana.draw(pokemonFront_Sprite);

		// CAPA 2: Interfaz (HUD, menús, barras)
		ventana.draw(bar_sprite);
		ventana.draw(enemyBar_sprite);
		ventana.draw(userBar_sprite);
				
        
        // Mostrar lo dibujado en pantalla
        ventana.display();
    }
    
    return 0;
}
