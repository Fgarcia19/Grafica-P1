#include <iostream>
#include "Camara.h"
#include <stdlib.h>
#include <time.h>
void escena();
void mover_luciernagas(vector<Objeto*> &objs, vector<Luz*> &luces);
int main() {
    srand (time(NULL));

    escena();

    return 0;
}

void escena() {
    vector<Objeto*> objetos;
    vector<Luz*> luces;

    Objeto *p1;

    //Luciernagas
    for(int i=0;i<4;i++){
        vec3 posLuz1(5+rand() %  41 + -20,60+rand() %  41 + -20,0+rand() %  41 + -20);
        vec3 colorLuz1(1,1,0);
        p1 = new Esfera(posLuz1, 3, colorLuz1);
        p1->es_luz = true;
        objetos.emplace_back(p1);
        Luz *pLuz = new Luz(posLuz1, colorLuz1);
        luces.emplace_back(pLuz);
    }

    //Frasco
    p1 = new Cilindro(vec3(5,4,0), vec3(5,140,0),50, vec3(0,1,1));
    p1->setConstantes(0.7,0.3,8);
    p1->setConstantes(0.5,0.5,8);
    p1->es_transparente = true;
    p1->ior = 1.3;
    objetos.emplace_back(p1);
    //Tapa
    p1 = new Cilindro(vec3(5,140,0), vec3(5,150,0),50, vec3(0.1451,0.1569,0.3137));
    p1->setConstantes(0,0);
    objetos.emplace_back(p1);

    //Objetos
    p1 = new Esfera(vec3(-90,30,5), 10, vec3(1,0.1,0.1));
    p1->setConstantes(0.8, 0.2);
    objetos.emplace_back(p1);

    p1 = new Cilindro(vec3(-90,0,-10), vec3(-90,20,-10),50, vec3(0.1451,0.1569,0.3137));
    p1->setConstantes(1,0);
    objetos.emplace_back(p1);

    p1 = new Esfera(vec3(90,30,-200), 30, vec3(0,1,0.1));
    p1->setConstantes(0.8, 0.2);
    objetos.emplace_back(p1);

    p1 = new Esfera(vec3(-160,30,-100), 30, vec3(1,0.1,0.1));
    p1->setConstantes(0.8, 0.2);
    objetos.emplace_back(p1);

    p1 = new Esfera(vec3(-300,200,-1100), 200, vec3(1,0.5,0.1));
    p1->setConstantes(0.8, 0.2);
    objetos.emplace_back(p1);

    p1 = new Cilindro(vec3(300,0,-1100), vec3(300,400,-1100),150, vec3(0.1451,0.1569,0.3137));
    p1->setConstantes(0.7,0.3);
    objetos.emplace_back(p1);

    p1 = new Cilindro(vec3(-110,0,120), vec3(-110,80,120),25, vec3(0.5,0.25,0));
    p1->setConstantes(1,0);
    objetos.emplace_back(p1);

    p1 = new Cilindro(vec3(110,0,200), vec3(110,40,200),50, vec3(0.1451,0.1569,0.3137));
    p1->setConstantes(1,0);
    objetos.emplace_back(p1);

    //Base
    p1 = new Plano(vec3(0,1,0), 1, vec3(0.123, 0.456, 0.789));
    p1->setConstantes(0.9, 0.1);
    p1->ke = 0.1;
    objetos.emplace_back(p1);

    //Movimientos de la camara
    Camara cam;
    int n = 1;
    for (int y = 1000; y > 500; y-=20){
        cam.configurar(3,60,600,800,
                       vec3(1,70,y),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(objetos, luces, n);
        mover_luciernagas(objetos, luces);
        n++;
    }
    for (int y = 1; y < 1000; y+=20){
        cam.configurar(3,60,600,800,
                       vec3(y,70,500),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(objetos, luces, n);
        mover_luciernagas(objetos, luces);
        n++;
    }
    for (int y = 500; y > 300; y-=20){
        cam.configurar(3,60,600,800,
                       vec3(980,70,y),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(objetos, luces, n);
        mover_luciernagas(objetos, luces);
        n++;
    }
    for (int y = 70; y < 300; y+=20){
        cam.configurar(3,60,600,800,
                       vec3(980,y,320),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(objetos, luces, n);
        mover_luciernagas(objetos, luces);
        n++;
    }

}

// Funcion para el movimiento de las luciernagas
void mover_luciernagas(vector<Objeto*> &objs, vector<Luz*> &luces)
{
    for(int i=0;i<luces.size();i++){
        luces[i]->pos.mover();
        dynamic_cast<Esfera*>(objs[i])->centro=luces[i]->pos;
    }
}