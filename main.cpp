#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Pokemon { // <-- Nombre de la clase
public:
    std::string nombre;
    int nivel;
    int vida;
    int vidamax;
    sf::Texture textura; // Faltaba el nombre de la variable
    sf::Sprite sprite;   // Faltaba el nombre de la variable
    std::string textoVida;
    std::string textoNivel;

    // EL CONSTRUCTOR DEBE LLAMARSE IGUAL QUE LA CLASE: PokemonUser
    Pokemon(std::string n, int lvl, int vMax, std::string rutaArchivo) {
        nombre = n;
        nivel = lvl;
        vidamax = vMax;
        vida = vMax;
        textoVida = std::to_string(vida) + " / " + std::to_string(vidamax);
        textoNivel = std::to_string(nivel);

        if (textura.loadFromFile(rutaArchivo)) {
            textura.setSmooth(false);
            sprite.setTexture(textura); // Ahora 'sprite' existe
        }
    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(sprite);
    }
};

int main() {
    // Crear la ventana (ancho, alto, título)
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pokemon Battle Simulator");
    
	Pokemon miCharmander("Charmander", 5, 200, "sprite/charmander_back.png");
	Pokemon enemyInstance("Pikachu", 67, 200, "sprite/pikachu_front.png");

    //Cargar Texturas
    
    sf::Texture backgroundBattle;
    backgroundBattle.loadFromFile("sprite/background.png");
    backgroundBattle.setSmooth(false);
    
    sf::Texture pokemonBack;
    pokemonBack.loadFromFile("sprite/charmander_back.png");
    pokemonBack.setSmooth(false);

    
    
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
    
    sf::Sprite pokemonFront_Sprite(enemyInstance.textura); //Pokemon Frontal Sprite
    pokemonFront_Sprite.setPosition(500.0f, 65.0f);
    pokemonFront_Sprite.setScale(4.0f, 4.0f);
    
    sf::Sprite pokemonBack_Sprite(miCharmander.textura); //Pokemon trasero Sprite
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

	//Fuente
	
	sf::Font fuente;
	fuente.loadFromFile("Pokemon.ttf");

    //Texto
    
    sf::Text enemyNameText; //Texto para Nombre del Enemigo
    enemyNameText.setString(enemyInstance.nombre);
    enemyNameText.setFont(fuente);
    enemyNameText.setCharacterSize(37);
    enemyNameText.setFillColor(sf::Color::Black);
    enemyNameText.setPosition(70.0f, 50.0f);
    
    sf::Text userNameText; //Texto para Nombre del Usuario
    userNameText.setString(miCharmander.nombre);
    userNameText.setFont(fuente);
    userNameText.setCharacterSize(37);
    userNameText.setFillColor(sf::Color::Black);
    userNameText.setPosition(485.0f, 320.0f);
    
     sf::Text infoText; //Texto para info
    infoText.setString("Charmander uso Mordisco\nFue super efectivo!");
    infoText.setFont(fuente);
    infoText.setCharacterSize(37);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(40.0f, 480.0f);
    
     sf::Text enemyLevel; //Texto para el nivel del enemigo
    enemyLevel.setString(enemyInstance.textoNivel);
    enemyLevel.setFont(fuente);
    enemyLevel.setCharacterSize(34);
    enemyLevel.setFillColor(sf::Color::Black);
    enemyLevel.setPosition(365.0f, 55.0f);
    
    sf::Text userVida; //Texto para la vida del usuario
    userVida.setString(miCharmander.textoVida);
    userVida.setFont(fuente);
    userVida.setCharacterSize(28);
    userVida.setFillColor(sf::Color::Black);
    userVida.setPosition(645.0f, 390.0f);
    
    
    // Loop principal de la aplicación
    while (ventana.isOpen()) {
        // Procesar todos los eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            // Si el usuario cierra la ventana
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            
            // Evento de Debug: Presionar Espacio
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Space) {
            // Obtenemos la posición del mouse RELATIVA a la ventana
            sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);
            
            // Imprimimos en la consola de Linux
            std::cout << "[DEBUG] Mouse Pos -> X: " << mousePos.x 
                      << " | Y: " << mousePos.y << std::endl;
        }
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
		ventana.draw(enemyNameText);
		ventana.draw(userNameText);
		ventana.draw(infoText);
		ventana.draw(enemyLevel);
		ventana.draw(userVida);
				
        
        // Mostrar lo dibujado en pantalla
        ventana.display();
    }
    
    return 0;
}
