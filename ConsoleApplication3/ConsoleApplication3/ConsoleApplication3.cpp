// ConsoleApplication3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <functional>
#include <string>
#include <cstdlib>

#include "Vec2.h"
#include "Vec2T.h"
#include "Arr.h"
#include "DynArr.h"
#include "IntArray.h"
#include "Node.hpp"
#include "Lib.hpp"

using namespace std;

void subFunction0() {
    Arr<int> foo(4);
    cout << foo.get(0) << endl;
    foo.get(0) = 33;
    cout << foo.get(0) << endl;
}

void subFunction1() {
    DynArr<int> foo(4);
    cout << foo.get(0) << endl;
    foo.get(0) = 33;
    cout << foo.get(0) << endl;

    foo.resize(16);
    
    for (int i = 0; i < 10; ++i) {
        cout << foo.get(i) << endl;
    }

    //foo.set(32, 64);
    auto stop = 6;
}

void StringCopy(char* dst, const char* src){
    while (*src != 0) {   //while value(src) is not zero
        *dst = *src; //copy value(src) in value(dst)
        src++; //advance src
        dst++; //advance dst
    }
};

int StringLength( const char * str ) {
    int count = 0;//creer un compteur
    while (*str)//tant que valeur(str) n 'est pas zero
    {
        str++; //  avancer str
        count++;//  incrementer le compteur
    }
    return count;//renvoyer la longueur qui est le compteur;
}

void subFunction2()
{
    std::string toto = "toto";
    cout << toto << endl;
    
    char toto2[5] = "toto";
    auto k = 0;
    int nb = StringLength(toto2);

    //char* sapin = new char[128];
    char sapin[128] = {};
    StringCopy(sapin, "lapin");
    cout << nb << endl;

    Node * root = new Node(10);
    root = root->heapify(9);// 9 fg 10
    root = root->heapify(11);// 9 fg 10 ...
    root = root->heapify(12);// 9 fg 10 ...
    
    if (!root->isOk()) throw "root is not a valid Heap";

    root = Node::merge(  root, new Node(12) );
    
    Node* tasFoireux = new Node(12, new Node(8), new Node(66));
    if (tasFoireux->isOk()) throw "lol nope le tas foireux est mal detecté";

    root = Node::merge(  root, tasFoireux);

    if (!root->isOk()) throw "root is not a valid Heap";
    auto s = 11;

    Node * n = new Node(1, new Node(2), new Node(3));
    n = n->deleteMin();
    if (!n->isOk()) throw "n is not a valid Heap";
    
    root = root->remove(12.0);

    if (!root->isOk()) throw "nroot is not a valid Heap";
}

DynArr<float> * doHeapSort(float* tab, int tabSize) {
    DynArr<float>* f = new DynArr<float>(tabSize);//create a new dyn array
    Node* root = new Node(tab[0]);//creer un premier noeud
    for (int i = 1; i < tabSize; ++i) //on ajouter d'autre noeud
        root = root->heapify(tab[i]);
    int idx = 0;//on a une racine root complete
    while (root) { // on depile la racine
        float val = root->getMin();//on recup le min
        f->set(idx, val);
        root = root->deleteMin();//on supprime
        idx++;
    }
    return f;//c'est trié
}

void heapSort() {
    float tf[4] = { 1.0,15.0,-1.0,25.0 };
    DynArr<float>* tab = doHeapSort(tf, 4);

    for (int i = 0; i < 4; ++i) {
        cout << tab->get(i)<<" ";
    }
    cout << endl;
}

void subFunction3() {
    DynArr<float>tab(0);
    for (int i = 0; i < 10; ++i)
        tab.set(i, i);
    tab.reverse();
    tab.push_back(16);

    DynArr<float>tab0(0);
    tab0.push_back(66);
    tab.append(tab0);
    
    std::function<void(float)> affiche = [](float elem) {
        printf("%f ", elem);
    };

    tab.iter(affiche);
    printf("\n");

    auto k = 0;
}


void MemCpy(char* dst, char* src, int size) {
    for (int i = 0; i < size; ++i) {//pour chaque caractere
        *dst = *src;//valeur(dst) = valeur(src)
        dst++;//avancer(dst)
        src++;//avancer(dst)
    }
}

//rechercher le char ou les chaines dans le contenu
char* StrChr(char* grange, char chat) {
    while (*grange) {
        if (*grange == chat)
            return grange;
           grange++;
    }
    return nullptr;
}

//"sapin\0"
int StrLen(char* meule) {
    int len = 0;
    while (*meule) {//apin puis pin puis ...
        meule++;//avance d'une case
        len++;
    }
    return len;// 
}

bool startsWith(char* meule, char* aiguille) {
    int lMeule = StrLen(meule);
    int lAiguille = StrLen(aiguille);
    
    if (lAiguille > lMeule)  return false;

    for( int i = 0; i < lAiguille;++i)
        if (aiguille[i] != meule[i])
            return false;

    return true;
}

//cherche l'aiguille dans la meule de foin
char* StrStr(char* meuleDeFoin, char* aiguille) {
    if (meuleDeFoin == nullptr) return nullptr;
    if (*meuleDeFoin == 0) return nullptr;
    if (startsWith(meuleDeFoin, aiguille))
        return meuleDeFoin;
    else
        return StrStr(meuleDeFoin+1, aiguille);
}

//reecrire int add(int a, int b) return a + b mais en utilisant la reccurence et +1 ou -1
//faire sub
//faire mul 
//faire div ( ouch ? )
//faire pow



int add(int a, int b) {//reecrire les additions avec seulement des -1 +1 1 et 0 
    if (b == 0)
        return a;
    if (b < 0)
        return -1 + add(a, b + 1);
    else 
        return 1 + add(a, b - 1);
}
//add( 2,3)
// 1 + add(2,2)
// 1 + 1 + add(2,1)
// 1 + 1 + 1 + add(2,0)
// 1 + 1 + 1 + 2
// 1 + 1 + 3
// 1 + 4
// 5  

//1 + ( 1+ ... )
// ...=> b fois

int sub(int a, int b) {
    if (b == 0)
        return a;
    if (b > 0)
        return -1 + sub(a, b - 1);// 4 3 => 1 + (4,2)
    else // 4 - -2 => 3 - -1
        return add(a, -b); //A -- B +> A+B
}


// mul(2,3)
// 2 + mul(2,2)
// 2 + 2 + mul(2,1)
// 2 + 2 + 2 +mul(2,0)
// 2 + 2 + 2 + 0 
// 2 + 2 + 2
// 2 + 4
// 6

// mul(2, -1)
// - mul(2,1)
// - ( 2 + mul(2,0))
// - ( 2 + 0)
// - ( 2 ) 
// - 2
int divEntiere(int a, int b) {
    if (b == 0) return 0;//throw ?
    if (b == 1) return a;// b == 1 => a

    if (b < 0) return -divEntiere(a, -b);// b < 0  => - a/b
    if (a < 0) return -divEntiere(-a, b);// a < 0 => - a /b 

    if (a < b) return 0;// cas a < b => 0

    return 1 + divEntiere(a-b, b);// div(a,b) => 1 + (a-b)/b
}

//renvoie le reste de la division de a par b
int modulo(int a, int b) {
    if (b == 0) return 0;
    if (b == 1) return 0;

    if (b < 0) return -modulo(a, -b);
    if (a < 0) return -modulo(-a, b);

    if (a < b) return a;
    
    return modulo(a - b, b);
}

int mul(int a, int b) {
    //revient a repeter une addition de a + ... a + a=> b fois
    //mul(a,b) = a + mul(a,b-1)

    if (b == 0)     return 0;
    else if (b > 0) return a + mul(a,b - 1);
    else if (b < 0) return - mul(a,-b);
}

// 1 si a est supérieur lexicographiqement à b
// 0 si a est egal lexicographiqument à b
// -1 si a est inférieur lexicographiqement à b

int StrCmp(const char* a, const char* b) {
    //si a est vide et b est vide rendre ?
    if (*a == 0 && *b == 0) return 0;
    if (*a == 0) return -1;//si a est vide
    if (*b == 0) return 1;//si a est vide
    //si valeur(a) > valeur(b)
    if (*a == *b)
        return StrCmp(a + 1, b + 1);
    
        //return ((*b - *a) > 0) ? -1 : 1;
    if (*a < *b)
        return -1;
    return 1;
    //si valeur(a) < b
    //sinon (valeur(a)==valeur(b)) rendre le resultat de la recurrence sur StrCmp(avancer(a),avancer(b)
}

void subFunction5() {
    cout << add(5, 6) << endl;
    cout << add(5, -6) << endl; 
    cout << sub(2, 3) << endl;
    cout << sub(2, -3) << endl;

    cout << mul(2, 2) << endl;
    cout << mul(2, -3) << endl;
    cout << mul(6, 10) << endl;

    cout << divEntiere(6, 10) << endl;
    cout << divEntiere(-60, 10) << endl;
    cout << divEntiere(60, -10) << endl;
    cout << divEntiere(6, 1) << endl;
    cout << divEntiere(60, 1) << endl;
    cout << divEntiere(6, 0) << endl;
    cout << divEntiere(-12, -6) << endl;
    cout << divEntiere(684846874, 345876) << endl;
    cout << divEntiere(6848468, 48684686) << endl;
    cout << modulo(15, 7) << endl;
    cout << modulo(-15, 7) << endl;
    cout << modulo(15, 20) << endl;
    cout << modulo(15, 3) << endl;
    
    cout << "start strcmp tests" << endl;
    cout << (StrCmp("a", "e") == -1) << endl;
    cout << (StrCmp("f", "a") == 1) << endl;
    cout << (StrCmp("aa", "b") == -1) << endl;
    cout << (StrCmp("", "") == 0) << endl;
    cout << (StrCmp("ab", "ab") == 0) << endl;
    cout << (StrCmp("ab", "aba") == -1) << endl;

    auto k = 66;
}

void subFunction4() {

    char data[] = { 66,1,2,3,4,5,6,67 };
    char* dest = (char*)malloc(16);
    for (int i = 0; i < 16; ++i) dest[i] = 0;

    MemCpy(dest, data, sizeof(data) * sizeof(char));

    for (int i = 0; i < 16; ++i)
        cout << (int)dest[i] << endl;
    free(dest);

    char foret[] = "sapinsapin";
    char sapin[] = "sapin";

    if (startsWith(foret, sapin)) {
        printf("forest begins with sapin");
    }
    else {
        printf("ERORO forest does not begins with sapin");
    }

    char pin[] = "pin";
    char* res = StrStr(foret, pin);
    if( res !=nullptr ) {
        printf("after pin in the forest : %s", res);
    }
    else {
        printf("ERORO forest does not begins with sapin");
    }
}

void subFunction6() {
    IntArray arrIota = IntArray::iota(6);
    IntArray arrRand = IntArray::random(6);

    {
        IntArray arr;
        arr.push_back(128);
        arr.push_front(5);
    }

    {
        IntArray arr;
        arr.push_front(6);
        arr.insert(0,3);
        arr.insert(20,8);
        auto stop = 66;
    }

    {
        IntArray arr = IntArray::iota(12);
        if (!arr.isSortedIter())
            throw "wut? iter";

        if (!arr.isSortedRec())
            throw "wut? rec";
    }

    {
        IntArray arr = IntArray::random(12);
        if (arr.isSortedRec())
            throw "wut? rec";
    }

    {
        IntArray arr;
        
        for (int i = 0; i < 1000; ++i) {
            int val = rand() % 150;
            int pos = arr.searchInsertionPosRec(val );
            arr.insert(pos, val);
        }

        if( ! arr.isSortedIter()) {
            throw "not sorted invariant is broken ?";
        }

        auto stop = 66;
    }

    

    {
        IntArray arr;
        arr.push_back(6);
        arr.push_back(6);
        arr.push_back(6);

        if (arr.binarySearch(77)) {
            throw "wtf?";
        }
    }

    {
        IntArray arr;
        arr.push_back(5);
        arr.push_back(6);
        arr.push_back(8);
        arr.push_back(8);
        arr.push_back(8);
        arr.push_back(8);
        arr.push_back(9);
        arr.push_back(10);

        int start = 0;
        
        if (!arr.binarySearch(5)) {
            throw "wtf?";
        }
        if (!arr.binarySearch(6)) {
            throw "wtf?";
        }
        if (!arr.binarySearch(9)) {
            throw "wtf?";
        }
        if (!arr.binarySearch(10)) {
            throw "wtf?";
        }
        if (arr.binarySearch(4)) {
            throw "wtf?";
        }
        if (arr.binarySearch(0)) {
            throw "wtf?";
        }
        if (arr.binarySearch(12)) {
            throw "wtf?";
        }
        if (arr.binarySearch(7)) {
            throw "wtf?";
        }
        auto stop = 66;

    }
   
    IntArray arr = IntArray::random(14000);
    double val0 = Lib::getTimeStamp();
    arr.sortInPlace();
    double val1 = Lib::getTimeStamp();
    cout << "temps ecoule : " << (val1 - val0) << "s" << endl;

    
    auto stop = 66;
};

int main()
{
    //subFunction0();
    //subFunction1();
    //subFunction2();
    //heapSort();
    //subFunction3();
    //subFunction4();
    //subFunction5();
    subFunction6();

    cout << endl;
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
