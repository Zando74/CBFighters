#########################################################################
#  _____ ____  ______ _____ _____ _    _ _______ ______ _____   _____   #
#  / ____|  _ \|  ____|_   _/ ____| |  | |__   __|  ____|  __ \ / ____| #
# | |    | |_) | |__    | || |  __| |__| |  | |  | |__  | |__) | (___   #
# | |    |  _ <|  __|   | || | |_ |  __  |  | |  |  __| |  _  / \___ \  #
# | |____| |_) | |     _| || |__| | |  | |  | |  | |____| | \ \ ____) | #
#  \_____|____/|_|    |_____\_____|_|  |_|  |_|  |______|_|  \_\_____/  #
#                                                                       #
#########################################################################
Informations factuelles :

Auteurs : - Payen Ferrer 11807073
	  - Benali Amir
	  - Nekkaa Jessim 11805614
	  - Magnin Constantin

Lien Forge Lyon 1 : https://forge.univ-lyon1.fr/p1805614/cbfighters

#########################################################################
Manuel d'utilisation : 

I - Compilation :
Executer la commande Make dans le répertoire du projet

II - Execution :
Dans le repertoire bin se trouve deux exécutable, test et game.

1) test est un programme executant les test de regressions des différents modules
Une fois lancé les test s'effectue automatiquement et le programme se termine tout seul.

2) game est le programme du jeu, une fois lancé il vous est demandé de choisir quel mode de jeu
vous souhaitez entre texte et graphique pour cela il suffit d'entrer "txt" ou "sdl" et d'appuyer sur entrée.

III - Règle et utilisation :

1) MODE TEXTE
En mode texte il vous est possible de de déplacer les personnages representée sous forme de caractère dans une grille, et de jouer des coups,
en mode texte un coup fait juste évoluer le caractère du personnage il n'y a pas de dégats possible.
notons P1 le joueur a gauche, P2 le joueur a droite :

            	  Touches pour P1 :               |	           Touches pour P2 :
            'q' : deplacement a gauche            |            'x' : deplacement a gauche
            'd' : deplacement a droite            |            'v' : deplacement a droite
            'u' : petit coup de poing             |            '7' : petit coup de poing
            'i' : moyen coup de poing             |            '8' : moyen coup de poing
	
								
	SORTIE DE PROGRAMME : CTRL + C

2) MODE GRAPHIQUE (SDL)
En mode graphique il existe plus de fonctionnalités, plus de coups sont possibles et des combinaison de touches peuvent etre effectués:
notons P1 le joueur a gauche, P2 le joueur a droite :

/* ATTENTION : LES COMBINAISON DE TOUCHES DE DIRECTIONS SONT SUSCEPTIBLE DE S'INVERSER DANS LE CAS OU LES JOUEURS PASSE DERRIERE LEURS ADVERSAIRE 
   Par exemple : pour les sauts en diagonal */

            	  Touches pour P1 :               |	           Touches pour P2 :
                                                  |
	    'z' : saut                            |            'fleche du haut' : saut
            'q' : deplacement a gauche ou blocage |            'fleche de gauche' : deplacement a gauche ou blocage   
                  si l'autre joueur met un coup   |                                 si l'autre joueur met un coup
            's' : s'accroupir                     |            'fleche du bas' : s'accroupir
            'd' : deplacement a droite            |            'fleche de droite' : deplacement a droite
            'u' : petit coup de poing             |            '7' : petit coup de poing
            'i' : moyen coup de poing             |            '8' : moyen coup de poing
            'o' : gros coup de poing              |            '9' : gros coup de poing
            'j' : petit coup de pied              |            '4' : petit coup de pied
            'k' : moyen coup de pied              |            '5' : moyen coup de pied
            'l' : gros coup de pied               |            '6' : gros coup de pied
						  |
	                         COMBINAISONS SIMULTANEE POSSIBLES
						  |
	   'z + q' : saut diagonal arriere        |            'fleche du haut + fleche de droite' : saut diagonal arriere
	   'z + d' : saut diagonal avant          |            'fleche du haut + fleche de gauche' : saut diagonal avant 
           's + une touche de coup' : le coup     |            's + une touche de coup' : le coup associé
	    associé en position accroupis         |            en position accroupis.
                                                  |
                                      MECANIQUES DU COUP SPECIAL
                                                  |
      'S' puis  'S + D' puis 'U' ou 'I' ou 'O'    |
   en moins de 160ms dans cette ordre précisement |
	donne le Special 1 : Hadoken              |          FONCTIONNE SIMETRIQUEMENT / il existe cependant quelques bugs a corriger
						  |		
      'S' puis 'S + Q' puis 'J' ou 'K' ou 'L'     |
  en moins de 160ms dans cette ordre précisement  |
   donne le Special 2 : Tatsumaki senpu kiaku     |
	

				SORTIE DE PROGRAMME : 'ECHAP'

Regle du jeu : 
Il s’agit d’un jeu de combat en 2D qui se joue en 1 contre 1.
Chaque joueur contrôle un personnage et affronte l’autre dans un match se déroulant en 2
round gagnant. Un round dure 99 secondes, le round est accordé au survivant
de la mêlée ou au joueur ayant le plus de vie à la fin du temps imparti.
Les joueurs peuvent se déplacer horizontalement en appuyant sur les touches
avant et arrière. Sauter sur place en appuyant sur la touche haut, vers l’avant en
appuyant sur haut + avant et vers l’arrière avec haut + arrière. Et enfin
s’accroupir en appuyant sur bas, bas + avant ou bas + arrière.
Pour infliger des dégâts à leur adversaire ils peuvent effectuer des coups
normaux en appuyant sur l’un des 6 boutons (lp : low punch, mp : middle punch, hp : high punch, lk : low kick, mk : middle kick, hk : high kick) en étant
debout, accroupis ou en sautant. Des coups spéciaux en faisant une combinaison
successive de directions puis l’un des boutons (par exemple : bas -> bas + avant
-> avant -> lp). 
dans le but d’infliger des dégâts à sa barre de vie, 
Ainsi, pour se défendre, le joueur devra maintenir la direction opposée à
l’adversaire (gauche ou droite) pour bloquer les coups hauts et moyens mais
restera vulnérable aux coups bas. Pour bloquer ces derniers il devra maintenir
bas en plus de la direction opposée à l’adversaire (donc bas + gauche ou bas + 
droite) Quand un coup est bloqué il
n’enlève que très peu de vie à celui qui le reçoit. 
Les projections quant à elle passent à travers la garde, le seul
moyen de les éviter est de faire la commande de projection peu après que
l’adversaire ai commencé à projeter le joueur pour annuler sa projection, ou de
sauter car un adversaire au sol ne peut pas projeter un joueur qui est dans les
airs.
Expliquons plus en détail ce qu’il se passe quand un joueur effectue un coup.
Tous les coups sont divisés en 3 lapses de temps. Les frames de démarrage,
pendant lesquelles le personnage joue l’animation du coup qui se prépare. Les
frames actives, pendant lesquelles des boites de collisions apparaissent sur le
joueur qui frappe afin qu’il puisse toucher son adversaire. Et enfin, les frames de
récupération, pendant lesquelles le personnage ayant fini son coup revient à
l’état neutre. Quand un coup est reçu par un joueur il sera étourdi pendant un
très petit lapse de temps qui change selon les coups et selon si le joueur à réussi
à bloquer ou s’il s’est fait toucher. Ainsi sur un adversaire qui bloque, les coups
ayant un temps de récupération court beaucoup pourrons
être utilisés en toute sécurité, tandis que les coups ayant de longs temps de
récupérations et qui étourdissent peu seront très dangereux à utiliser car
l’adversaire pourra riposter avec un coup au démarrage plus rapide que la
récupération du coup qu’il vient de bloquer. Enfin, quand le
joueur réussi à toucher son adversaire avec un coup, après sa récupération il est
possible pour lui de jouer un autre coup au démarrage plus rapide que la fin de
l’étourdissement de son adversaire afin d’effectuer un combo. Il est aussi
possible de faire un combo en annulant le temps de récupération d’un coup
normal avec un coup spécial. Quand un joueur effectue un combo un compteur
s’affiche pour annoncer le nombre de coups qu’il comportait, plus un combo
comporte de coups plus les dégâts qu’ils font sont réduits. Evidemment, pour
éviter les combos infinis, quand un joueur bloque ou se fait toucher par un coup
l’impact le pousse en arrière.

#########################################################################
ORGANISATIONS DE L'ARCHIVE

	 
	BIN           	  DATA              DOC                      OBJ              SRC               MAKEFILE
	/ \              / | \             /   \                      |              / | \
       /   \            /  |  \           /     \                    *.o            /  |  \
     game  test        /   |   \        html/   cbfighters.doxy                    /   |   \
		      /    |    \                                                 /    |    \
	     characters/  font/  map/                                          core/  sdl2/  txt/
										/      |      \
									    *.h/cpp  *.h/cpp  *.h/cpp
                          