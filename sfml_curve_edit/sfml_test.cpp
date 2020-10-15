// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Interp.hpp"

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

                static int colors[] = {
                    0x59EB7F,
                    0xE4F55D,
                    0xDEB65F,
                    0xF57F5D,
                    0xEB37E5 };
                
                static int choice = 0;
                choice = (choice+1)%5;
                Vertex v(Vector2f(event.mouseButton.x, event.mouseButton.y), Color((colors[choice]<<8) | 0xff));
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

        if( myPoints.size()>1)
        for (int i = 0; i < myPoints.size() ;i++) {
            //recuperer vtx i -1
            //recuperer vtx i 
            //recuperer vtx i + 1
            //recuperer vtx i + 2
            sf::Vertex v0 = (i == 0) ? myPoints[i] : myPoints[i-1];//i-1
            sf::Vertex v1 = myPoints[i];//i
            sf::Vertex v2 = ((i + 1) >= myPoints.size()) ? myPoints[myPoints.size() - 1] : myPoints[i + 1];//i;
            sf::Vertex v3 = ((i + 2) >= myPoints.size()) ? myPoints[myPoints.size() - 1] : myPoints[i + 2];//i

            //pour j  de 0...20
            //  t vaut 1 / j
            //  inserer catmull( v i-1, v i, v i +1, vi +2 , j / 20.0 ) 
            for (int j = 0; j <= 20; j++) {
                float t = j/20.0;
                sf::Vector2f pos = Interp::c2(v0.position, v1.position, v2.position, v3.position, t); 

                sf::Color col;
                col.a = 255;
                col.r = Interp::catmull( v0.color.r, v1.color.r, v2.color.r, v3.color.r, t);
                col.g = Interp::catmull( v0.color.g, v1.color.g, v2.color.g, v3.color.g, t);;
                col.b = Interp::catmull( v0.color.b, v1.color.b, v2.color.b, v3.color.b, t);;

                line.append(sf::Vertex(pos, col));
            }
         }
        
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
