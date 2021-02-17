//
// Created by nino on 24/03/2020.
//

#ifndef CBFIGHTERS_SPRITEMANAGER_H
#define CBFIGHTERS_SPRITEMANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include "../core/Player.h"

class SpriteManager {

public:
    /**
     * @brief Le constructeur de la classe pour un joueur.
     * @param p : Le joueur associé à la sprite.
     * @param ren : Le renderer.
     */
    SpriteManager(Player & p, SDL_Renderer * ren);
    /**
     * @brief Le destructeur de la classe.
     */
    ~SpriteManager();
    /**
     * @brief Charge un sprite dans la variable currentSprite de la classe.
     * @param fileName : Chemin du sprite à charger.
     * @param renderer
     */
    void LoadSprite(std::string fileName, SDL_Renderer * renderer);
    /**
     * @brief Actualise la sprite du joueur passé en paramètre.
     * @param p : Le joueur
     * @param otherPlayerPosX : La position du joueur adverse, utilisée pour dessiner la sprite du joueur de façon à toujours faire face à l'adversaire.
     */
    void updateSprite(Player & p,int otherPlayerPosX);
    /**
     * @brief Dessine la sprite du joueur passé en paramètre.
     * @param p : Le joueur
     * @param otherPlayerPosX : La position du joueur adverse.
     */
    void renderSprite(Player & p,int otherPlayerPosX);
    /**
     * @brief Retourne la largeur de la sprite.
     * @return
     */
    int getSpriteWidth();
    /**
     * @brief Retourne la hauteur de la sprite.
     * @return
     */
    int getSriteHeight();
    /**
     * @brief Constructeur de la classe pour la map.
     * @param fighterName : nom du personnage de la map.
     * @param ren
     */
    SpriteManager(std::string & fighterName, SDL_Renderer * ren);
    /**
     * @brief Actualise la sprite de la map et sa position, et la position des deux joueurs sur l'écran afin qu'elles correspondent à leurs positions sur la map.
     * @param p1 : Le joueur 1.
     * @param p2 : Le joueur 2.
     */
    void updateMap(Player & p1,Player & p2);
    /**
     * @brief Dessine la map sur l'écran.
     */
    void renderMap();

private:
    int frameCounter;
    int frameCounterTimer;
    int screenWidth, screenHeight;
    int mapWidth, mapHeight;
    void setSpriteSize(Player & p);
    std::string mapName;
    SDL_Texture * currentSprite;
    SDL_Rect srcRect, dstRect;
    SDL_Renderer * renderer;
    SDL_RendererFlip spriteFlip;
};


#endif //CBFIGHTERS_SPRITEMANAGER_H
