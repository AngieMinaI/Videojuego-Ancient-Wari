#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_BULLETS = 100;
const int MAX_ENEMY_BULLETS = 100;
const int MAX_ENEMIES = 3;
bool isLevel1MusicPlaying = false;
bool isLevel2MusicPlaying = false;
bool isLevel3MusicPlaying = false;

struct Bullet {
    sf::RectangleShape shape;
    bool isActive;

    Bullet() : isActive(false) {
        shape.setSize(sf::Vector2f(5, 20));
        shape.setFillColor(sf::Color::Yellow);
    }
};

struct EnemyBullet {
    sf::RectangleShape shape;
    bool isActive;

    EnemyBullet() : isActive(false) {
        shape.setSize(sf::Vector2f(5, 20));
        shape.setFillColor(sf::Color::Red);
    }
};

struct Enemy {
    sf::Sprite sprite;
    bool isActive;

    Enemy() : isActive(true) {}
};

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    sf::RenderWindow window(sf::VideoMode(800, 800), "Proyecto Final");

    sf::Texture backgroundTexture0;
    if (!backgroundTexture0.loadFromFile("fondo_inicio.png")) {
        std::cerr << "Error al cargar la textura del fondo" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite0;
    backgroundSprite0.setTexture(backgroundTexture0);
    backgroundSprite0.setScale(
        window.getSize().x / backgroundSprite0.getGlobalBounds().width,
        window.getSize().y / backgroundSprite0.getGlobalBounds().height
    );
    
    // Carga de fondo de pantalla de los niveles
    // 1
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("fondo1_pikillaqta.jpg")) {
        std::cerr << "Error al cargar la textura del fondo" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
    );
    // 2
    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("fondo2_huiracochapampa.jpg")) {
        std::cerr << "Error al cargar la textura del fondo" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite2;
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setScale(
        window.getSize().x / backgroundSprite2.getGlobalBounds().width,
        window.getSize().y / backgroundSprite2.getGlobalBounds().height
    );
    // 3
    sf::Texture backgroundTexture3;
    if (!backgroundTexture3.loadFromFile("fondo3_vegachayuq_mogo.jpg")) {
        std::cerr << "Error al cargar la textura del fondo" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite3;
    backgroundSprite3.setTexture(backgroundTexture3);
    backgroundSprite3.setScale(
        window.getSize().x / backgroundSprite3.getGlobalBounds().width,
        window.getSize().y / backgroundSprite3.getGlobalBounds().height
    );
    
    
    
    


    //textura personaje
	sf::Texture texture;
    if (!texture.loadFromFile("pc.png")) {
        std::cerr << "Error al cargar la textura de la nave" << std::endl;
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(300, 600);
    float speed = 0.3f;
    sprite.setScale(1.8f, 1.8f);
    
    //texturas enemigas nivel 1
    sf::Texture enemyTexture1, enemyTexture2, enemyTexture3;
    if (!enemyTexture1.loadFromFile("urpu.png")) {
        std::cerr << "Error al cargar la textura del enemigo 1" << std::endl;
        return -1;
    }
    if (!enemyTexture2.loadFromFile("figura_zoomorfa.png")) {
        std::cerr << "Error al cargar la textura del enemigo 2" << std::endl;
        return -1;
    }
    if (!enemyTexture3.loadFromFile("urpu.png")) {
        std::cerr << "Error al cargar la textura del enemigo 3" << std::endl;
        return -1;
    }
    
    
    //texturas enemigas nivel 2
    sf::Texture enemyTexture4, enemyTexture5, enemyTexture6;
    if (!enemyTexture4.loadFromFile("cantaros.png")) {
        std::cerr << "Error al cargar la textura del enemigo 4" << std::endl;
        return -1;
    }
    if (!enemyTexture5.loadFromFile("vasija_antropomorfa.png")) {
        std::cerr << "Error al cargar la textura del enemigo 5" << std::endl;
        return -1;
    }
    if (!enemyTexture6.loadFromFile("cantaros.png")) {
        std::cerr << "Error al cargar la textura del enemigo 6" << std::endl;
        return -1;
    }
    
    //texturas enemigas nivel 3
    sf::Texture enemyTexture7, enemyTexture8, enemyTexture9;
    if (!enemyTexture7.loadFromFile("guerreros.png")) {
        std::cerr << "Error al cargar la textura del enemigo 7" << std::endl;
        return -1;
    }
    if (!enemyTexture8.loadFromFile("monolito.png")) {
        std::cerr << "Error al cargar la textura del enemigo 8" << std::endl;
        return -1;
    }
    if (!enemyTexture9.loadFromFile("guerreros.png")) {
        std::cerr << "Error al cargar la textura del enemigo 9" << std::endl;
        return -1;
    }
    
    
    //codigo enemigos nivel 1
    Enemy enemies[MAX_ENEMIES];
    sf::Clock enemyClocks[MAX_ENEMIES];
    sf::Time enemyChangeDirectionTimes[MAX_ENEMIES] = 
		{ sf::seconds(2.0f), sf::seconds(1.0f), sf::seconds(3.0f) };
    float enemySpeeds[MAX_ENEMIES] = { 0.1f, 0.1f, 0.1f };

    enemies[0].sprite.setTexture(enemyTexture1);
    enemies[0].sprite.setPosition(100, 15);
    enemies[0].sprite.setScale(0.7f, 0.7f);

    enemies[1].sprite.setTexture(enemyTexture2);
    enemies[1].sprite.setPosition(300, -25);
    enemies[1].sprite.setScale(0.3f, 0.3f);

    enemies[2].sprite.setTexture(enemyTexture3);
    enemies[2].sprite.setPosition(500, 15);
    enemies[2].sprite.setScale(0.7f, 0.7f);

    Bullet bullets[MAX_BULLETS];
    sf::Clock bulletClock;
    sf::Time bulletCooldown = sf::seconds(1.0f);

    EnemyBullet enemyBullets[MAX_ENEMY_BULLETS];
    sf::Clock enemyBulletClock;
    sf::Time enemyBulletCooldown = sf::seconds(1.0f);
    
    //codigo enemigos nivel 2
    Enemy enemieslvl2[MAX_ENEMIES];
    sf::Clock enemyClockslvl2[MAX_ENEMIES];
    sf::Time enemyChangeDirectionTimeslvl2[MAX_ENEMIES] = { sf::seconds(1.5f), sf::seconds(1.0f), sf::seconds(2.0f) };
    float enemySpeedslvl2[MAX_ENEMIES] = { 0.1f, 0.1f, 0.1f };

    enemieslvl2[0].sprite.setTexture(enemyTexture4);
    enemieslvl2[0].sprite.setPosition(100, 15);
    enemieslvl2[0].sprite.setScale(0.3f, 0.3f);

    enemieslvl2[1].sprite.setTexture(enemyTexture5);
    enemieslvl2[1].sprite.setPosition(300, -25);
    enemieslvl2[1].sprite.setScale(0.3f, 0.3f);

    enemieslvl2[2].sprite.setTexture(enemyTexture6);
    enemieslvl2[2].sprite.setPosition(500, 15);
    enemieslvl2[2].sprite.setScale(0.3f, 0.3f);

    Bullet bulletslvl2[MAX_BULLETS];
    sf::Clock bulletClocklvl2;
    sf::Time bulletCooldownlvl2 = sf::seconds(1.0f);

    EnemyBullet enemyBulletslvl2[MAX_ENEMY_BULLETS];
    sf::Clock enemyBulletClocklvl2;
    sf::Time enemyBulletCooldownlv2 = sf::seconds(0.8f);
    
    //codigo enemigos nivel 3
    
    Enemy enemieslvl3[MAX_ENEMIES];
    sf::Clock enemyClockslvl3[MAX_ENEMIES];
    sf::Time enemyChangeDirectionTimeslvl3[MAX_ENEMIES] = { sf::seconds(1.5f), sf::seconds(1.0f), sf::seconds(2.0f) };
    float enemySpeedslvl3[MAX_ENEMIES] = { 0.13f, 0.13f, 0.13f };

    enemieslvl3[0].sprite.setTexture(enemyTexture7);
    enemieslvl3[0].sprite.setPosition(100, 15);
    enemieslvl3[0].sprite.setScale(0.3f, 0.3f);

    enemieslvl3[1].sprite.setTexture(enemyTexture8);
    enemieslvl3[1].sprite.setPosition(300, -25);
    enemieslvl3[1].sprite.setScale(0.3f, 0.3f);

    enemieslvl3[2].sprite.setTexture(enemyTexture9);
    enemieslvl3[2].sprite.setPosition(500, 15);
    enemieslvl3[2].sprite.setScale(0.3f, 0.3f);

    Bullet bulletslvl3[MAX_BULLETS];
    sf::Clock bulletClocklvl3;
    sf::Time bulletCooldownlvl3 = sf::seconds(1.0f);

    EnemyBullet enemyBulletslvl3[MAX_ENEMY_BULLETS];
    sf::Clock enemyBulletClocklvl3;
    sf::Time enemyBulletCooldownlv3 = sf::seconds(0.8f);
    
    
    //
    
    sf::Font font;
    if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return -1;
    }

    sf::Text startText2("Presiona ENTER para comenzar", font, 25);
    startText2.setFillColor(sf::Color::Blue);
    startText2.setPosition(50, 190);
    
    sf::Text startText6(" ° ANCIENT WARI ° ", font, 25);
    startText6.setFillColor(sf::Color::Red);
    startText6.setPosition(200, 10);
    
    sf::Text startText3("Integrantes", font, 30);
    startText3.setFillColor(sf::Color::Red);
    startText3.setPosition(430, 700);
    
    sf::Text startText4("Angie Mina Ishuiza", font, 20);
    startText4.setFillColor(sf::Color::Black);
    startText4.setPosition(400, 740);
    
    sf::Text startText5("Daniel Purizaca Sanchez", font, 20);
    startText5.setFillColor(sf::Color::Black);
    startText5.setPosition(300, 770);

    sf::Font font1;
    if (!font1.loadFromFile("Anton-Regular.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return -1;
    }
    
    // codigo cargar sonidos
    
    sf::Music musicaFondo;
	if (!musicaFondo.openFromFile("Sonidos/corazon_mio.wav")) {
	    std::cerr << "Error al cargar la música de la pantalla principal" << std::endl;
	    return -1;
	}
	musicaFondo.setLoop(true);
	
	sf::Music musicaFondolvl2;
	if (!musicaFondolvl2.openFromFile("Sonidos/AmorHerido.wav")) {
	    std::cerr << "Error al cargar la música de la pantalla principal" << std::endl;
	    return -1;
	}
	musicaFondolvl2.setLoop(true);
	
	sf::Music musicaFondolvl3;
	if (!musicaFondolvl3.openFromFile("Sonidos/AdiosPuebloAyacucho.wav")) {
	    std::cerr << "Error al cargar la música de la pantalla principal" << std::endl;
	    return -1;
	}
	musicaFondolvl3.setLoop(true);
    
    
    sf::SoundBuffer disparoBuffer;
    if (!disparoBuffer.loadFromFile("Sonidos/Disparo_1.wav")) {
        std::cerr << "Error al cargar el sonido de disparo" << std::endl;
        return -1;
    }
    sf::Sound disparoSound;
    disparoSound.setBuffer(disparoBuffer);
    
    /*sf::SoundBuffer enemyDisparoBuffer;
    if (!enemyDisparoBuffer.loadFromFile("Sonidos/Disparo_2.wav")) { 
        std::cerr << "Error al cargar el sonido de disparo enemigo" << std::endl;
        return -1;
    }
    sf::Sound enemyDisparoSound;
    enemyDisparoSound.setBuffer(enemyDisparoBuffer);
    */
    sf::SoundBuffer roturaBuffer;
    if (!roturaBuffer.loadFromFile("Sonidos/Rotura.wav")) {
        std::cerr << "Error al cargar el sonido de disparo" << std::endl;
        return -1;
    }
    sf::Sound roturaSound;
    roturaSound.setBuffer(roturaBuffer);
    
    sf::SoundBuffer roturaPCBuffer;
    if (!roturaPCBuffer.loadFromFile("Sonidos/ImpactoPC.wav")) {
        std::cerr << "Error al cargar el sonido de disparo" << std::endl;
        return -1;
    }
    sf::Sound roturaPCSound;
    roturaPCSound.setBuffer(roturaPCBuffer);
    
    // codigo puntaje
    sf::Text scoreText;
    scoreText.setFont(font1);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    int score = 0;
    scoreText.setPosition(620,710);
    scoreText.setString("Puntaje: " + std::to_string(score));
    
    // codigo vida
    sf::Text lifeText("Vida", font1, 30);
    lifeText.setFillColor(sf::Color::Black);
    lifeText.setPosition(50, 710);
    
    int playerLifeCounter = 100;
    sf::RectangleShape lifeBarBackground(sf::Vector2f(300, 20));
    lifeBarBackground.setFillColor(sf::Color::Red);
    lifeBarBackground.setPosition(50, 750);

    sf::RectangleShape lifeBar(sf::Vector2f(300, 20));
    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setPosition(50, 750);

    bool isGameStarted = false;
    bool isGameOver = false;
    sf::Clock gameOverClock;

    sf::Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 400);
    
    sf::Text winningText("¡You Win!", font, 50);
    winningText.setFillColor(sf::Color::Blue);
    winningText.setPosition(200, 400);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!isGameStarted) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                isGameStarted = true;
            }
        } else if (!isGameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (sprite.getPosition().x > 0) {
                    sprite.move(-speed, 0);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (sprite.getPosition().x + sprite.getGlobalBounds().width < window.getSize().x) {
                    sprite.move(speed, 0);
                }
            }
            
            
            // nivel 1
            
            if (score >= 0 && score <150){
            	
            	if (!isLevel1MusicPlaying) {
	                musicaFondo.play();
	                isLevel1MusicPlaying = true;
	                isLevel2MusicPlaying = false;
	                isLevel3MusicPlaying = false;
	            }
	            if (musicaFondolvl2.getStatus() == sf::SoundSource::Playing) {
	                musicaFondolvl2.stop();
	            }
	            if (musicaFondolvl3.getStatus() == sf::SoundSource::Playing) {
	                musicaFondolvl3.stop();
	            }

            	
            	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletClock.getElapsedTime() >= bulletCooldown) {
	                for (int i = 0; i < MAX_BULLETS; ++i) {
	                    if (!bullets[i].isActive) {
	                        bullets[i].shape.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 2.5f, sprite.getPosition().y);
	                        bullets[i].isActive = true;
	                        disparoSound.play();
	                        bulletClock.restart();
	                        break;
	                    }
	                }
	            }
            	
            	
            	for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bullets[i].isActive) {
	                    bullets[i].shape.move(0, -0.2f);
	                    if (bullets[i].shape.getPosition().y < 0) {
	                        bullets[i].isActive = false;
	                    }
	                }
	            }

	            if (enemyBulletClock.getElapsedTime() >= enemyBulletCooldown) {
	                for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                    if (!enemyBullets[i].isActive) {
	                        int randomEnemy = std::rand() % MAX_ENEMIES;
	                        if (!enemies[randomEnemy].isActive) continue;
	                        sf::Sprite* enemySprite = &enemies[randomEnemy].sprite;
	                        enemyBullets[i].shape.setPosition(enemySprite->getPosition().x + enemySprite->getGlobalBounds().width / 2 - 2.5f, enemySprite->getPosition().y + enemySprite->getGlobalBounds().height);
	                        enemyBullets[i].isActive = true;
	                        //enemyDisparoSound.play();
	                        enemyBulletClock.restart();
	                        break;
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBullets[i].isActive) {
	                    enemyBullets[i].shape.move(0, 0.2f);
	                    if (enemyBullets[i].shape.getPosition().y > window.getSize().y) {
	                        enemyBullets[i].isActive = false;
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_ENEMIES; ++i) {
	                if (enemyClocks[i].getElapsedTime() >= enemyChangeDirectionTimes[i]) {
	                    enemySpeeds[i] = (std::rand() % 2 == 0 ? -1.0f : 1.0f) * (0.1f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.2f)));
	                    enemyClocks[i].restart();
	                }
	                if (enemies[i].isActive) {
	                    enemies[i].sprite.move(enemySpeeds[i], 0);
	                    if (enemies[i].sprite.getPosition().x < 0 || enemies[i].sprite.getPosition().x + enemies[i].sprite.getGlobalBounds().width > window.getSize().x) {
	                        enemySpeeds[i] = -enemySpeeds[i];
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bullets[i].isActive) {
	                    for (int j = 0; j < MAX_ENEMIES; ++j) {
	                        if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].
								sprite.getGlobalBounds()) && enemies[j].isActive) {
	                        	score += 50;
	                        	scoreText.setString("Puntaje: " + std::to_string(score));  //actualizar puntaje
	                            bullets[i].isActive = false;
	                            enemies[j].isActive = false;
	                            roturaSound.play();
	                            enemies[j].sprite.setPosition(-100, -100); // Mover enemigo fuera de la pantalla
	                        }
	                    }
	                }
	            }
	            
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBullets[i].isActive) {
	                    if (enemyBullets[i].shape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
	                        enemyBullets[i].isActive = false;
	                        playerLifeCounter -= 20;
	                        roturaPCSound.play();
	                        if (playerLifeCounter <= 0) {
	                            isGameOver = true;
	                            gameOverClock.restart();
	                        }
	                    }
	                }
	            }
			}
            
            // nivel 2
            if (score>=150 && score <300){
            	
            	
            	if (!isLevel2MusicPlaying) {
	                musicaFondo.stop();
	                musicaFondolvl2.play();
	                isLevel1MusicPlaying = false;
	                isLevel2MusicPlaying = true;
	                isLevel3MusicPlaying = false;
	            }
	            if (musicaFondo.getStatus() == sf::SoundSource::Playing) {
	                musicaFondo.stop();
	            }
	            if (musicaFondolvl3.getStatus() == sf::SoundSource::Playing) {
	                musicaFondolvl3.stop();
	            }
	            
	            
            	
            	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletClocklvl2.getElapsedTime() >= bulletCooldownlvl2) {
				    for (int i = 0; i < MAX_BULLETS; ++i) {
				        if (!bulletslvl2[i].isActive) {
				            bulletslvl2[i].shape.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 2.5f, sprite.getPosition().y);
				            bulletslvl2[i].isActive = true;
				            disparoSound.play();
				            bulletClocklvl2.restart();
				            break;
				        }
				    }
				}
            	
            	
	            for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bulletslvl2[i].isActive) {
	                    bulletslvl2[i].shape.move(0, -0.2f);
	                    if (bulletslvl2[i].shape.getPosition().y < 0) {
	                        bulletslvl2[i].isActive = false;
	                    }
	                }
	            }
	
	            if (enemyBulletClocklvl2.getElapsedTime() >= enemyBulletCooldownlv2) {
	                for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                    if (!enemyBulletslvl2[i].isActive) {
	                        int randomEnemy = std::rand() % MAX_ENEMIES;
	                        if (!enemieslvl2[randomEnemy].isActive) continue;
	                        sf::Sprite* enemySprite = &enemieslvl2[randomEnemy].sprite;
	                        enemyBulletslvl2[i].shape.setPosition(enemySprite->getPosition().x + enemySprite->getGlobalBounds().width / 2 - 2.5f, enemySprite->getPosition().y + enemySprite->getGlobalBounds().height);
	                        enemyBulletslvl2[i].isActive = true;
	                        //enemyDisparoSound.play();
	                        enemyBulletClocklvl2.restart();
	                        break;
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBulletslvl2[i].isActive) {
	                    enemyBulletslvl2[i].shape.move(0, 0.2f);
	                    if (enemyBulletslvl2[i].shape.getPosition().y > window.getSize().y) {
	                        enemyBulletslvl2[i].isActive = false;
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_ENEMIES; ++i) {
	                if (enemyClockslvl2[i].getElapsedTime() >= enemyChangeDirectionTimes[i]) {
	                    enemySpeedslvl2[i] = (std::rand() % 2 == 0 ? -1.0f : 1.0f) * (0.1f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.2f)));
	                    enemyClockslvl2[i].restart();
	                }
	                if (enemieslvl2[i].isActive) {
	                    enemieslvl2[i].sprite.move(enemySpeedslvl2[i], 0);
	                    if (enemieslvl2[i].sprite.getPosition().x < 0 || enemieslvl2[i].sprite.getPosition().x + enemieslvl2[i].sprite.getGlobalBounds().width > window.getSize().x) {
	                        enemySpeedslvl2[i] = -enemySpeedslvl2[i];
	                    }
	                }
	            }
	            
            	for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bulletslvl2[i].isActive) {
	                    for (int j = 0; j < MAX_ENEMIES; ++j) {
	                        if (bulletslvl2[i].shape.getGlobalBounds().intersects(enemieslvl2[j].sprite.getGlobalBounds()) && enemieslvl2[j].isActive) {
	                        	score += 50;
	                        	scoreText.setString("Puntaje: " + std::to_string(score)); //actualizar puntaje
	                            bulletslvl2[i].isActive = false;
	                            enemieslvl2[j].isActive = false;
	                            roturaSound.play();
	                            enemieslvl2[j].sprite.setPosition(-100, -100); // Mover enemigo fuera de la pantalla
	                        }
	                    }
	                }
            	}
            	
            	for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBulletslvl2[i].isActive) {
	                    if (enemyBulletslvl2[i].shape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
	                        enemyBulletslvl2[i].isActive = false;
	                        playerLifeCounter -= 20;
	                        roturaPCSound.play();
	                        if (playerLifeCounter <= 0) {
	                            isGameOver = true;
	                            gameOverClock.restart();
	                        }
	                    }
	                }
            	}
			}
            
            // nivel 3
            
            if (score>=300 && score <450){
            	
            	if (!isLevel3MusicPlaying) {
	                musicaFondolvl2.stop();
	                musicaFondolvl3.play();
	                isLevel1MusicPlaying = false;
	                isLevel2MusicPlaying = false;
	                isLevel3MusicPlaying = true;
	            }
	            if (musicaFondo.getStatus() == sf::SoundSource::Playing) {
	                musicaFondo.stop();
	            }
	            if (musicaFondolvl2.getStatus() == sf::SoundSource::Playing) {
	                musicaFondolvl2.stop();
	            }
            	
            	
            	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletClocklvl3.getElapsedTime() >= bulletCooldownlvl3) {
				    for (int i = 0; i < MAX_BULLETS; ++i) {
				        if (!bulletslvl3[i].isActive) {
				            bulletslvl3[i].shape.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 2.5f, sprite.getPosition().y);
				            bulletslvl3[i].isActive = true;
				            disparoSound.play();
				            bulletClocklvl3.restart();
				            break;
				        }
				    }
				}
            	
            	
	            for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bulletslvl3[i].isActive) {
	                    bulletslvl3[i].shape.move(0, -0.2f);
	                    if (bulletslvl3[i].shape.getPosition().y < 0) {
	                        bulletslvl3[i].isActive = false;
	                    }
	                }
	            }
	
	            if (enemyBulletClocklvl3.getElapsedTime() >= enemyBulletCooldownlv3) {
	                for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                    if (!enemyBulletslvl3[i].isActive) {
	                        int randomEnemy = std::rand() % MAX_ENEMIES;
	                        if (!enemieslvl3[randomEnemy].isActive) continue;
	                        sf::Sprite* enemySprite = &enemieslvl3[randomEnemy].sprite;
	                        enemyBulletslvl3[i].shape.setPosition(enemySprite->getPosition().x + enemySprite->getGlobalBounds().width / 2 - 2.5f, enemySprite->getPosition().y + enemySprite->getGlobalBounds().height);
	                        enemyBulletslvl3[i].isActive = true;
	                        //enemyDisparoSound.play();
	                        enemyBulletClocklvl3.restart();
	                        break;
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBulletslvl3[i].isActive) {
	                    enemyBulletslvl3[i].shape.move(0, 0.2f);
	                    if (enemyBulletslvl3[i].shape.getPosition().y > window.getSize().y) {
	                        enemyBulletslvl3[i].isActive = false;
	                    }
	                }
	            }
	
	            for (int i = 0; i < MAX_ENEMIES; ++i) {
	                if (enemyClockslvl3[i].getElapsedTime() >= enemyChangeDirectionTimes[i]) {
	                    enemySpeedslvl3[i] = (std::rand() % 2 == 0 ? -1.0f : 1.0f) * (0.1f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.2f)));
	                    enemyClockslvl3[i].restart();
	                }
	                if (enemieslvl3[i].isActive) {
	                    enemieslvl3[i].sprite.move(enemySpeedslvl3[i], 0);
	                    if (enemieslvl3[i].sprite.getPosition().x < 0 || enemieslvl3[i].sprite.getPosition().x + enemieslvl3[i].sprite.getGlobalBounds().width > window.getSize().x) {
	                        enemySpeedslvl3[i] = -enemySpeedslvl3[i];
	                    }
	                }
	            }
	            
            	for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bulletslvl3[i].isActive) {
	                    for (int j = 0; j < MAX_ENEMIES; ++j) {
	                        if (bulletslvl3[i].shape.getGlobalBounds().intersects(enemieslvl3[j].sprite.getGlobalBounds()) && enemieslvl3[j].isActive) {
	                        	score += 50;
	                        	scoreText.setString("Puntaje: " + std::to_string(score)); //actualizar puntaje
	                            bulletslvl3[i].isActive = false;
	                            enemieslvl3[j].isActive = false;
	                            roturaSound.play();
	                            enemieslvl3[j].sprite.setPosition(-100, -100); // Mover enemigo fuera de la pantalla
	                        }
	                    }
	                }
            	}
            	
            	for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBulletslvl3[i].isActive) {
	                    if (enemyBulletslvl3[i].shape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
	                        enemyBulletslvl3[i].isActive = false;
	                        roturaPCSound.play();
	                        playerLifeCounter -= 20;
	                        if (playerLifeCounter <= 0) {
	                            isGameOver = true;
	                            gameOverClock.restart();
	                        }
	                    }
	                }
            	}
			}
            
            float lifeRatio = static_cast<float>(playerLifeCounter) / 100.0f;
            lifeBar.setSize(sf::Vector2f(300 * lifeRatio, 20));
            lifeBar.setFillColor(sf::Color(255 * (1 - lifeRatio), 255 * lifeRatio, 0));
        }

        window.clear();
        if (!isGameStarted) {
            window.draw(backgroundSprite0);
            window.draw(startText2);
            window.draw(startText3);
            window.draw(startText4);
            window.draw(startText5);
            window.draw(startText6);
        } else if (isGameOver) {
            window.draw(backgroundSprite0);
            window.draw(gameOverText);
        } else {
            if(score >= 0 && score < 150){
            	window.draw(backgroundSprite);
	            window.draw(sprite);
	            for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bullets[i].isActive) {
	                    window.draw(bullets[i].shape);
	                }
	            }
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBullets[i].isActive) {
	                    window.draw(enemyBullets[i].shape);
	                }
	            }
	            for (int i = 0; i < MAX_ENEMIES; ++i) {
	                if (enemies[i].isActive) {
	                    window.draw(enemies[i].sprite);
	                }
	            }
			} else if(score >=150 && score < 300){
				window.draw(backgroundSprite2);
	            window.draw(sprite);
	            for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bulletslvl2[i].isActive) {
	                    window.draw(bulletslvl2[i].shape);
	                }
	            }
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBulletslvl2[i].isActive) {
	                    window.draw(enemyBulletslvl2[i].shape);
	                }
	            }
	            for (int i = 0; i < MAX_ENEMIES; ++i) {
	                if (enemieslvl2[i].isActive) {
	                    window.draw(enemieslvl2[i].sprite);
	                }
	            }
			} else if(score >=300 && score < 450){
				window.draw(backgroundSprite3);
	            window.draw(sprite);
	            for (int i = 0; i < MAX_BULLETS; ++i) {
	                if (bulletslvl3[i].isActive) {
	                    window.draw(bulletslvl3[i].shape);
	                }
	            }
	            for (int i = 0; i < MAX_ENEMY_BULLETS; ++i) {
	                if (enemyBulletslvl3[i].isActive) {
	                    window.draw(enemyBulletslvl3[i].shape);
	                }
	            }
	            for (int i = 0; i < MAX_ENEMIES; ++i) {
	                if (enemieslvl3[i].isActive) {
	                    window.draw(enemieslvl3[i].sprite);
	                }
	            }
			} else if (score == 450){
				window.draw(backgroundSprite0);
				window.draw(winningText);
			}
            window.draw(lifeText);
            window.draw(lifeBarBackground);
            window.draw(lifeBar);
            window.draw(scoreText);
        }

        window.display();
    }

    return 0;
}

