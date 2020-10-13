// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>


int main()
{
    std::cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode(640, 480,32), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;

        sf::Vector2f dir(0, 0);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                {
                    int a = 0xFAA35Aff; //0xFAA35A 00 0xFAA35A
                    int b = 0xDE4E26ff;
                    int c = 0xF5363Cff;
                    int d = 0xDE26BDff;
                    int e = 0xB92BFFff;

                    sf::Color col;
                    if( event.key.code == sf::Keyboard::F1 )  col = sf::Color(a);
                    if( event.key.code == sf::Keyboard::F2 )  col = sf::Color(b);
                    if( event.key.code == sf::Keyboard::F3 )  col = sf::Color(c);
                    if( event.key.code == sf::Keyboard::F4 )  col = sf::Color(d);
                    if( event.key.code == sf::Keyboard::F5 )  col = sf::Color(e);
                    shape.setFillColor(col);
                }
            }
            //sinon si mouse event
            // deplacer la sphere sous le event.x/.y

            if (event.type == sf::Event::MouseMoved) {
                shape.setOrigin(shape.getRadius(), shape.getRadius());
                shape.setPosition(event.mouseMove.x, event.mouseMove.y);
            }

            if (event.type == sf::Event::MouseWheelScrolled ) {
                int rad = shape.getRadius();
                rad += event.mouseWheelScroll.delta;
                if (rad < 10) rad = 10;
                shape.setRadius(rad);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )    dir.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))     dir.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    dir.x++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))       dir.y--;
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);

        float sp = 0.33;

        if (len > 0 ) {
            dir.x /= len;
            dir.y /= len;

            dir.x *= sp;
            dir.y *= sp;

            auto pos = shape.getPosition();
            pos.x += dir.x;
            pos.y += dir.y;
            shape.setPosition(pos);
        }

        window.clear();
        window.draw(shape);
        auto pos = shape.getPosition();
        pos.x += 0.00;
        shape.setPosition(pos);
        window.display();
    }

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
