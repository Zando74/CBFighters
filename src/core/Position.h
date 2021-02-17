/**
@brief Module gérant positions de nos personnages.

 Une position correspond un point dans un espace a deux dimension.
 Ce point peut etre deplacé dans l'espaces.
 @file Position.h
 @date 2020/04/20
 */

#ifndef CBFIGHTERS_POSITION_H
#define CBFIGHTERS_POSITION_H

class Position {
/**
@brief La classe Position contient nos 2 coordonnée x,y.
*/
private :
	int x;
	int y;

public :
	/**
    * @brief Construit l'objet Position.
    */
	Position();
	/**
    * @brief detruit l'objet Position.
    */
	~Position();
	/**
    * @brief accesseur de la donnée membre x.
    */
	int getPosX();
	/**
    * @brief accesseur de la donnée membre y.
    */
	int getPosY();
	/**
    * @brief mutateur de la donnée membre x.
	* @param posX : un entier
    */
	void setPosX(const int & posX);
	/**
    * @brief mutateur de la donnée membre x.
	* @param posY : un entier
    */
	void setPosY(const int & posY);
	/**
    * @brief incremente x de 4.
    */
	void moveRight();
	/**
    * @brief décremente x de 4.
    */
	void moveLeft();
	/**
    * @brief incremente y.
    */
	void neutralJump();
	/**
    * @brief incremente x et y.
    */
	void forwardJump();
	/**
    * @brief décremente x et y.
    */
	void backwardJump();

};

#endif  //CBFIGHTERS_POSITION_H