//
// Created by nino on 24/03/2020.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include "SpriteManager.h"
#include "../core/Player.h"

SpriteManager::SpriteManager(Player & p, SDL_Renderer * ren) {
    renderer = ren;
    currentSprite = NULL;
    LoadSprite("data/characters/" + p.getMyFighter().getFighterName() + "/" + p.getPlayerState() + "/" + p.getBodyFighter() + ".png",renderer);
    setSpriteSize(p);
    srcRect.x = 0;
    srcRect.y = 0;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}

SpriteManager::SpriteManager(std::string & fighterName, SDL_Renderer *ren) {
    mapName = fighterName;
    mapWidth = 620;
    mapHeight = 224;
    screenWidth = 384;
    screenHeight = 224;
    frameCounter = 1;
    frameCounterTimer = 0;
    renderer = ren;
    LoadSprite("data/map/" + mapName + "/" + std::to_string(frameCounter) + ".png",renderer);
    srcRect.w = screenWidth;
    srcRect.h = screenHeight;
    srcRect.x = 310 - srcRect.w/2;
    srcRect.y = 0;
    dstRect.w = screenWidth;
    dstRect.h = screenHeight;
    dstRect.x = 0;
    dstRect.y = 0;
}

SpriteManager::~SpriteManager() {
    SDL_DestroyTexture(currentSprite);
}

void SpriteManager::updateSprite(Player & p,int otherPlayerPosX) {
    LoadSprite("data/characters/" + p.getMyFighter().getFighterName() + "/" + p.getPlayerState() + "/" + p.getBodyFighter() + ".png",renderer);
    setSpriteSize(p);
    dstRect.x = p.getPositionX() - srcRect.w/2;
    dstRect.y = p.getPositionY() - srcRect.h;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
    spriteFlip = SDL_FLIP_NONE;
}

void SpriteManager::renderSprite(Player & p,int otherPlayerPosX) {
    if(p.getPositionX() > otherPlayerPosX)
        spriteFlip = SDL_FLIP_HORIZONTAL;
    else
        spriteFlip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer,currentSprite,&srcRect,&dstRect,0,NULL,spriteFlip);
}

void SpriteManager::LoadSprite(std::string fileName, SDL_Renderer *renderer) {
    SDL_Surface * tmpSurface = IMG_Load(fileName.c_str());
    if(currentSprite != NULL){
        SDL_DestroyTexture(currentSprite);
    }
    currentSprite = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void SpriteManager::setSpriteSize(Player &p) {
    std::ifstream moveSprite("data/characters/" + p.getMyFighter().getFighterName() + "/" + p.getPlayerState() + "/" + p.getBodyFighter() + ".png");
    int width, height;
    moveSprite.seekg(16);
    moveSprite.read((char *)&width, 4);
    moveSprite.read((char *)&height,4);
    moveSprite.close();
    srcRect.w = ntohl(width);
    srcRect.h = ntohl(height);
}

void SpriteManager::updateMap(Player & p1, Player & p2) {
    p1.setPositionOnMap(srcRect.x + p1.getPositionX());
    p2.setPositionOnMap(srcRect.x + p2.getPositionX());
    if (frameCounter == 13)
        frameCounter = 1;
    LoadSprite("data/map/" + mapName + "/" + std::to_string(frameCounter) + ".png", renderer);
    int playerPosXAvg = (p1.getPositionOnMap() + p2.getPositionOnMap()) / 2;
    int tmp;
    if(playerPosXAvg > screenWidth/2 && playerPosXAvg < mapWidth - screenWidth/2) {
        tmp = srcRect.x;
        srcRect.x = playerPosXAvg - srcRect.w/2;
        tmp = tmp - srcRect.x;
        p1.getPosition().setPosX(p1.getPositionX() + tmp);
        p2.getPosition().setPosX(p2.getPositionX() + tmp);
    }
    if(frameCounterTimer == 15)
    {
        frameCounter++;
        frameCounterTimer = 0;
    }
    frameCounterTimer++;
}

void SpriteManager::renderMap() {
    SDL_RenderCopy(renderer,currentSprite,&srcRect,&dstRect);
}

int SpriteManager::getSpriteWidth() {
    return srcRect.w;
}

int SpriteManager::getSriteHeight() {
    return srcRect.h;
}