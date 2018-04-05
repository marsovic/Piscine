#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.charger_graphe("graphe_terre.txt");


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();
//
//        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    //sauvegarder
    /*for(int i = 0; i < g.m_vertices.size() ; i++) // i(idx d'un graphe) jusqu'au nombre de graphe chargé ( taille de la map )
    {
        //remplir les fichiers selon m_vertices et m_egdes ( ils sont remplis à chaque add_interfaced_vertex/edge )
        //Voir fichier pour comprendre la structure !
    }*/

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


