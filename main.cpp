#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

enum StateMachine {TURNO_JUGADOR, MENSAJE_ATAQUE, TURNO_ENEMIGO, FIN_COMBATE}; //Estados del State Machine

float hpbar_ancho; //Variables de el tamaño de la barra hp del usuario y el enemigo, no tocar
const float hpbar_total_ancho = 193.0f;
const float hpbar_total_altura = 12.0f;

class Pokemon { // <-- Nombre de la clase
public:
    std::string nombre;
    int nivel;
    int vida;
    int vidamax;
    int atk;
    int def;
    int vel;
    int potencia; //El daño que quitara
    sf::Texture textura; // Faltaba el nombre de la variable
    sf::Sprite sprite;   // Faltaba el nombre de la variable
    std::string textoVida;
    std::string textoNivel;
    int danohecho; //Para cuanto daño recibira el enemigo

    // EL CONSTRUCTOR DEBE LLAMARSE IGUAL QUE LA CLASE: PokemonUser
    Pokemon(std::string n, int lvl, int vMax, std::string rutaArchivo, int atq, int defi, int speedi) {
        nombre = n;
        nivel = lvl;
        vidamax = vMax;
        vida = vMax;
        textoVida = std::to_string(vida) + " / " + std::to_string(vidamax); //para texto de las vidas ejemp 200 / 200
        textoNivel = std::to_string(nivel); //texto para nivel
        atk = atq;
        def = defi;
        vel = speedi;
        

        if (textura.loadFromFile(rutaArchivo)) {
            textura.setSmooth(false);
            sprite.setTexture(textura); // Ahora 'sprite' existe
        }
    }

	/* 
	 Funcion para recibir daño, dentro de la clase Pokemon
	 
	 
	  */


	void recibirDanio(int cantidad, sf::RectangleShape& barraVisual) { 
    vida -= cantidad;
    if (vida < 0) vida = 0;



    // Actualizamos el texto
    textoVida = std::to_string(vida) + " / " + std::to_string(vidamax);

    // CÁLCULO DE LA BARRA: Usamos static_cast<float> para no perder decimales
    float porcentaje = static_cast<float>(vida) / static_cast<float>(vidamax);
    float nuevoAncho = hpbar_total_ancho * porcentaje;

    // Aplicamos el tamaño a la barra que pasamos por parámetro
    barraVisual.setSize(sf::Vector2f(nuevoAncho, hpbar_total_altura));

    // Opcional: Cambiar color si queda poca vida
    if (porcentaje < 0.2f) barraVisual.setFillColor(sf::Color::Red);
    else if (porcentaje < 0.5f) barraVisual.setFillColor(sf::Color::Yellow);
}

	void CalcularDanio(std::string ataque, int potenciaatk, int defensaenemiga, int ataqueusuario, int nivelusuario){
		//Funcion para calcular daño
		float parte1 = (2.0f * nivelusuario / 5.0f) + 2;
		float parte2 = (parte1 * potenciaatk * (static_cast<float>(ataqueusuario) / defensaenemiga));
		
		int danoFinal = static_cast<int>((parte2 / 50.0f) + 2.0f);
		
		danohecho = danoFinal;
		
		
	}

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(sprite);
    }
};



int main() {
    // Crear la ventana (ancho, alto, título)
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pokemon Battle Simulator");
    
    // Creacion de las CLASES
	Pokemon userInstance("Charmander", 5, 18, "sprite/charmander_back.png", 10, 8, 16);
	Pokemon enemyInstance("Squirtle", 5, 19, "sprite/squirtle_front.png", 9, 9, 14);
	
	
	StateMachine estado_Actual;
	//Variable Enum de State Machine
	
	if (userInstance.vel > enemyInstance.vel){
	
	estado_Actual = TURNO_JUGADOR;
	
} else {
		estado_Actual = TURNO_ENEMIGO;

}
	
	//Variable Const 
	
	
	
	//Rectangulo HP BAR
	
	sf::RectangleShape hpenemyblank; //Rectangulo en blanco del enemigo
	hpenemyblank.setSize(sf::Vector2f(hpbar_total_ancho, hpbar_total_altura));
	hpenemyblank.setPosition(193.0f, 106.0f);
	hpenemyblank.setFillColor(sf::Color::Black);
	
	sf::RectangleShape hpenemygreen; //Rectangulo en verde del enemigo
	hpenemygreen.setSize(sf::Vector2f(hpbar_total_ancho, hpbar_total_altura));
	hpenemygreen.setPosition(193.0f, 106.0f);
	hpenemygreen.setFillColor(sf::Color::Green);
	
	sf::RectangleShape hpuserblank; //Rectangulo en blanco del usuario
	hpuserblank.setSize(sf::Vector2f(hpbar_total_ancho, hpbar_total_altura));
	hpuserblank.setPosition(564.0f, 364.0f);
	hpuserblank.setFillColor(sf::Color::Black);
	
	sf::RectangleShape hpusergreen; //Rectangulo en verde del usuario
	hpusergreen.setSize(sf::Vector2f(hpbar_total_ancho, hpbar_total_altura));
	hpusergreen.setPosition(564.0f, 364.0f);
	hpusergreen.setFillColor(sf::Color::Green);

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
    
    sf::Sprite backgroundBattle_sprite(backgroundBattle); //Fondo
    backgroundBattle_sprite.setPosition(0.0f, 0.0f);
    backgroundBattle_sprite.setScale(3.5f, 4.2f);
    
    sf::Sprite pokemonFront_Sprite(enemyInstance.textura); //Pokemon Frontal Sprite
    pokemonFront_Sprite.setPosition(500.0f, 65.0f);
    pokemonFront_Sprite.setScale(4.0f, 4.0f);
    
    sf::Sprite pokemonBack_Sprite(userInstance.textura); //Pokemon trasero Sprite
    pokemonBack_Sprite.setPosition(40.0f, 240.0f);
    pokemonBack_Sprite.setScale(4.0f, 4.0f);
    
    //Sprite HUD
    
    sf::Sprite enemyBar_sprite(enemyBar); //Barra enemiga
    enemyBar_sprite.setPosition(30.0f, 30.0f);
    enemyBar_sprite.setScale(4.0f, 4.0f);
    
    sf::Sprite userBar_sprite(userBar); //Bara del player
    userBar_sprite.setPosition(372.0f, 280.0f);
    userBar_sprite.setScale(4.0f, 4.0f);
    
    sf::Sprite bar_sprite(bar); //Barra de Fondo
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
    userNameText.setString(userInstance.nombre);
    userNameText.setFont(fuente);
    userNameText.setCharacterSize(37);
    userNameText.setFillColor(sf::Color::Black);
    userNameText.setPosition(437.0f, 310.0f);
    
     sf::Text infoText; //Texto para info
     if (estado_Actual == TURNO_JUGADOR){
    infoText.setString(userInstance.nombre + " anda esperando tu eleccion.\nPresiona los numeros del 1 al 4");
} else {
	infoText.setString(enemyInstance.nombre + " espera para atacar.");
}
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
    userVida.setString(userInstance.textoVida);
    userVida.setFont(fuente);
    userVida.setCharacterSize(28);
    userVida.setFillColor(sf::Color::Black);
    userVida.setPosition(645.0f, 390.0f);
    
    sf::Text userLevel; //Texto para el nivel del usuario
    userLevel.setString(userInstance.textoNivel);
    userLevel.setFont(fuente);
    userLevel.setCharacterSize(34);
    userLevel.setFillColor(sf::Color::Black);
    userLevel.setPosition(739.0f, 317.0f);
    
    sf::Clock relojEnemigo;
    bool relojReiniciado = false;
    
    
    // Loop principal de la aplicación
    while (ventana.isOpen()) {
        // Procesar todos los eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
			/*
			 ###################
			 
			 EVENTO POLL
			 
			 
			 ###################
			  */
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
        
        /*##########ATAQUE DEL USUARIO#############
         *  
         ##########################################*/
        if (evento.type == sf::Event::KeyPressed){ //Checa si se presiono una tecla
			if (estado_Actual == TURNO_JUGADOR){ //Checa si es mi turno
				//ATAQUE 1 DEL USUARIO
				if (evento.key.code == sf::Keyboard::Num1){ //Checa si se presiono la tecla 1
					
					userInstance.CalcularDanio("Aranazo", 40, enemyInstance.def, userInstance.atk, userInstance.nivel);
					enemyInstance.recibirDanio(userInstance.danohecho, hpenemygreen);
					
					infoText.setString(userInstance.nombre + " ha utilizado aranazo.");
					if (enemyInstance.vida > 0){
					estado_Actual = TURNO_ENEMIGO;
				} else {
					estado_Actual = FIN_COMBATE;
					infoText.setString(enemyInstance.nombre + " Se ha debilitado\nHas ganado.");
					
				}
					
					
					
					//ATAQUE 2 DEL USUARIO
				} else if (evento.key.code == sf::Keyboard::Num2){ //Checa si se presiono la tecla 2
					
					enemyInstance.recibirDanio(0, hpenemygreen);
					enemyInstance.atk -= 2;
					if (enemyInstance.atk > 1){   // El ataque no puede ser menor a 3
					
					infoText.setString(userInstance.nombre + " ha utilizado Grunido.\nEl ataque de " + enemyInstance.nombre + " ha bajado.");
				} else {
					enemyInstance.atk = 1;
					infoText.setString(userInstance.nombre + " ha utilizado Grunido.\nEl ataque de " + enemyInstance.nombre + " no puede bajar mas.");

					
				}
					if (enemyInstance.vida > 0){
					estado_Actual = TURNO_ENEMIGO;
				} else {
					estado_Actual = FIN_COMBATE;
					infoText.setString(enemyInstance.nombre + " Se ha debilitado\nHas ganado.");
					
				}
				//ATAQUE 3 DEL USUARIO
				} else if (evento.key.code == sf::Keyboard::Num3){ //Checa si se presiono la tecla 3
					
					userInstance.CalcularDanio("Ascuas", 60, enemyInstance.def, userInstance.atk, userInstance.nivel);
					enemyInstance.recibirDanio(userInstance.danohecho, hpenemygreen);
					
					infoText.setString(userInstance.nombre + " ha utilizado Ascuas.\nEs super efectivo.");
					if (enemyInstance.vida > 0){
					estado_Actual = TURNO_ENEMIGO;
				} else {
					estado_Actual = FIN_COMBATE;
					infoText.setString(enemyInstance.nombre + " Se ha debilitado\nHas ganado.");
					
				}
				}
				
				
				
				
				
			}
			
			
			
			
			
		}
    }
            
            // Si presiona la tecla ESC
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Escape) {
                    ventana.close();
                }
            }
            
            
            
            
           
				
				
				
				
			}
			
			// TURNO DE RIVAL
            
			
			 if (estado_Actual == TURNO_ENEMIGO){
				
				if (!relojReiniciado) {
					relojEnemigo.restart();
					relojReiniciado = true;
				}
				
				if (relojEnemigo.getElapsedTime().asSeconds() >= 1.5f) {
				
				enemyInstance.CalcularDanio("Placaje", 40, userInstance.def, enemyInstance.atk, enemyInstance.nivel);
				userInstance.recibirDanio(enemyInstance.danohecho, hpusergreen);
				userVida.setString(userInstance.textoVida);
				infoText.setString(enemyInstance.nombre + " ha utilizado Placaje.");
				relojReiniciado = false;
				if (userInstance.vida > 0){
				estado_Actual = TURNO_JUGADOR;
			} else {
				estado_Actual = FIN_COMBATE;
				infoText.setString(userInstance.nombre + " se ha debilitado\nHas perdido");
			}

				
			}
			
			
        }
        
        if (estado_Actual == FIN_COMBATE){
				
				if (!relojReiniciado) {
					relojEnemigo.restart();
					relojReiniciado = true;
				}
				
				if (relojEnemigo.getElapsedTime().asSeconds() >= 5.0f){
					std::cout<<"Esto llega aqui";
					ventana.close();
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
		ventana.draw(userLevel);
		ventana.draw(hpenemyblank);
		ventana.draw(hpenemygreen);
		ventana.draw(hpuserblank);
		ventana.draw(hpusergreen);
				
        
        // Mostrar lo dibujado en pantalla
        ventana.display();
    }
    
    return 0;
}
