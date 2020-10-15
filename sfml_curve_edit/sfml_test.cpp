// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;


int main()
{
    cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode(1280, 720,32), "SFML works!");

    Text text;
    Font font;
    vector<Vertex> myPoints;
   
    VertexArray line(PrimitiveType::LineStrip);
    myPoints.push_back(Vertex(Vector2f(50, 50), Color(0x5DFFA3ff)));
    myPoints.push_back(Vertex(Vector2f(500, 500), Color(0xF5363Cff)));
    myPoints.push_back(Vertex(Vector2f(50, 500), Color(0xF5363Cff)));

    if (!font.loadFromFile("res/MAIAN.TTF")) {
        cout << "ERROR NO FONT" << endl;
        return 1;
    }

    // charger une fonte ?
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                //si backspace 
                //reset tout les points
                if( event.key.code == sf::Keyboard::Key::BackSpace)
                    myPoints.clear();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
               //ajouter un point
               //add a vertex
                Vertex v(Vector2f(event.mouseButton.x, event.mouseButton.y), Color(0x5DFFA3ff));
                myPoints.push_back(v);
            }
            
        }
        
        text.setFont(font);
        text.setString("Touche Backspace pour supprimer les points");
        text.setCharacterSize(24);
        text.setPosition(0, 0);
        text.setFillColor(Color::White);

        //recreate all the line each frame
        line.clear();
        for (Vertex& vtx : myPoints) 
            line.append(vtx);
        
        window.clear();
        
        window.draw(text);
        window.draw(line);

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
