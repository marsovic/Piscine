#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(100, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    // m_top_box.add_child( m_slider_value );
    // m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
    // m_slider_value.set_dim(20,80);
    // m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    //
    // // Label de visualisation de valeur
    // m_top_box.add_child( m_label_value );
    // m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    //m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    //m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    //m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    //Bouton graphe 1
    m_tool_box.add_child(m_bouton_graph1);
    m_bouton_graph1.set_frame(3,3,80,80);
    m_bouton_graph1.set_bg_color(BLEUCLAIR);
    m_bouton_graph1.add_child(m_bouton1_label);
    m_bouton1_label.set_message("Graphe 1");

    //Bouton graphe 2
    m_tool_box.add_child(m_bouton_graph2);
    m_bouton_graph2.set_frame(3,93,80,80);
    m_bouton_graph2.set_bg_color(ROUGECLAIR);
    m_bouton_graph2.add_child(m_bouton2_label);
    m_bouton2_label.set_message("Graphe 2");

    //Bouton graphe 3
    m_tool_box.add_child(m_bouton_graph3);
    m_bouton_graph3.set_frame(3,183,80,80);
    m_bouton_graph3.set_bg_color(VERTCLAIR);
    m_bouton_graph3.add_child(m_bouton3_label);
    m_bouton3_label.set_message("Graphe 3");

    //Label Sommet
    m_tool_box.add_child(m_label_sommet);
    m_label_sommet.set_frame(3,275,40,40);
    m_label_sommet.set_message("Sommet :");

    //Bouton Ajouter_Sommet
    m_tool_box.add_child(m_bouton_add_vertex);
    m_bouton_add_vertex.set_frame(3,293,80,80);
    m_bouton_add_vertex.set_bg_color(CYAN);
    m_bouton_add_vertex.add_child(m_bouton_add_vertex_label);
    m_bouton_add_vertex_label.set_message("Ajouter");

    //Bouton Supprimer_Sommet
    m_tool_box.add_child(m_bouton_del_vertex);
    m_bouton_del_vertex.set_frame(3,383,80,80);
    m_bouton_del_vertex.set_bg_color(ORANGECLAIR);
    m_bouton_del_vertex.add_child(m_bouton_del_vertex_label);
    m_bouton_del_vertex_label.set_message("Supprimer");

    //Label Methode
    m_tool_box.add_child(m_label_arete);
    m_label_arete.set_frame(3,465,40,40);
    m_label_arete.set_message("Methodes :");

    //Bouton ForteCo
    m_tool_box.add_child(m_bouton_add_edge);
    m_bouton_add_edge.set_frame(3,485,80,80);
    m_bouton_add_edge.set_bg_color(CYAN);
    m_bouton_add_edge.add_child(m_bouton_add_edge_label);
    m_bouton_add_edge_label.set_message("ForteCo");

    //Bouton ?
    m_tool_box.add_child(m_bouton_del_edge);
    m_bouton_del_edge.set_frame(3,575,80,80);
    m_bouton_del_edge.set_bg_color(ORANGECLAIR);
    m_bouton_del_edge.add_child(m_bouton_del_edge_label);
    m_bouton_del_edge_label.set_message("?");
}


/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent �tre d�finis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent �tre d�finis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    changer_graphe();

    if(this->m_interface->m_bouton_add_vertex.clicked())
    //Bouton graphe1 , voir graph.h dans GraphInterface !
    {
      int choix;
      do{
        std::cout << "Quel sommet voulez vous ajouter ?" << std::endl;
        std::cin >> choix;
      }while(choix>m_vertices.size());

      ajouter_sommet(choix);
    }
    if(this->m_interface->m_bouton_del_vertex.clicked())
    //Bouton graphe1 , voir graph.h dans GraphInterface !
    {
      int choix;

      do{
        std::cout << "Quel sommet voulez vous supprimer ?" << std::endl;
        std::cin >> choix;
      }while(choix>m_vertices.size());
      supprimer_sommet(choix);
    }

    if(this->m_interface->m_bouton_add_edge.clicked())
    //Bouton graphe1 , voir graph.h dans GraphInterface !
    {
      chercher_forte_connexite();
    }


}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);

    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}

void Graph::charger_graphe(std::string fichier)//Fichier est le nom du fichier dans le dossier du projet(Ex : "graphe_terre.txt")
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600); //Initialisation de l'interface de graphe !
    std::fstream fic(fichier, std::ios::in | std::ios::out ); // On ouvre un flux pour le fichier
    if(fic)
    {

        std::string name,chemin; //Nom et chemin jusqu'a l'image
        int idx,idx_arete,x,y,ordre,nb_aretes,s1,s2; // Idx pour sommet et ar�te , coordonn�es x,y pour les sommets
        //le nombre d'ar�te pour les parcourir et s1 et s2 les sommets d'une ar�te
        float poids;
        double pop;
        fic >> m_identifiant;
        fic >> ordre;                                // Voir le fichier pour mieux comprendre la r�cup des donn�es.
        for(int i =0; i< ordre; i++)
        {
//            fic.ignore('-',':');
            fic >> name;
//            fic.ignore('-',':');
            fic >> idx;
//            fic.ignore('-',':');
            fic >> pop;
//            fic.ignore('-',':');
            fic >> x;
//            fic.ignore('-',':');
            fic >> y;
//            fic.ignore('*','*');
            fic >> chemin;

            add_interfaced_vertex(idx,pop,x,y,chemin,i); // Cette m�thode ajoute un sommet � la map m_vertices
                                                        //et l'affiche , elle prends en param�tre ce qu'on a lu

        }
        set_idx_ver_max(ordre);

            fic >> nb_aretes;
            for(int j =0 ; j< nb_aretes ; j++)
            {
                fic >> idx_arete;
                fic >> s1;
                fic >> s2;
                fic >> poids;
                add_interfaced_edge(idx_arete,s1,s2,poids); // Cette m�thode ajoute une ar�te � la map m_edges et l'affiche.
            }
            set_idx_edge_max(nb_aretes);


        fic.close();

    }

    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
}

void Graph::sauvegarder_graphe(std::string fichier)
{
    std::ofstream fic(fichier, std::ios::out| std::ios::trunc );
    if(fic)
    {
        fic << m_identifiant << " " << std::endl;
        fic << m_vertices.size() << " " << std::endl;
        for(auto i = m_vertices.begin(); i!=m_vertices.end(); ++i) //Ecriture de la liste des sommmets avec leurs infos
        {
            fic << "NomEspece" << " ";
            fic << i->first << " ";
            fic << i->second.m_value << " ";
            fic << i->second.m_interface->m_top_box.get_posx() << " ";
            fic << i->second.m_interface->m_top_box.get_posy() << " ";
            fic << i->second.m_interface->m_img.get_pic_name() << std::endl;
        }

        fic << m_edges.size() << std::endl;
        for(auto i = m_edges.begin(); i!=m_edges.end(); i++)
        {
            fic << i->first << " ";
            fic << i->second.m_from << " ";
            fic << i->second.m_to << " ";
            fic << i->second.m_weight << std::endl;
        }
        fic.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
}

void Graph::changer_graphe()
{
  std::stringstream path;
  path << "graphe_" << m_identifiant << ".txt";
  sauvegarder_graphe(path.str());
  //std::cout << path.str() << std::endl;
  if(this->m_interface->m_bouton_graph1.clicked())
  //Bouton graphe1 , voir graph.h dans GraphInterface !
  {
    for(int i = 0; i< this->m_vertices.size(); i++)
    {
        m_interface->m_main_box.remove_child(m_vertices[i].m_interface->m_top_box);
    }
    m_vertices.clear();
    for(int i = 0; i< this->m_edges.size(); i++)
    {
        m_interface->m_main_box.remove_child(m_edges[i].m_interface->m_top_edge);
    }
    m_edges.clear();
    rest(500);
    charger_graphe("graphe_marin.txt");
  }

  if(this->m_interface->m_bouton_graph2.clicked())
  //Bouton graphe2 , voir graph.h dans GraphInterface !
  {
    for(int i = 0; i< this->m_vertices.size(); i++)
    {
        m_interface->m_main_box.remove_child(m_vertices[i].m_interface->m_top_box);
    }
    m_vertices.clear();
    for(int i = 0; i< this->m_edges.size(); i++)
    {
        m_interface->m_main_box.remove_child(m_edges[i].m_interface->m_top_edge);
    }
    m_edges.clear();
    rest(500);
    charger_graphe("graphe_savane.txt");
  }

  if(this->m_interface->m_bouton_graph3.clicked())
  //Bouton graphe3 , voir graph.h dans GraphInterface !
  {
    // std::stringstream path;
    // path << "graphe_" << m_identifiant << ".txt";
    //sauvegarder_graphe(path.str());
    for(int i = 0; i< this->m_vertices.size(); i++)
    {
        m_interface->m_main_box.remove_child(m_vertices[i].m_interface->m_top_box);
    }
    m_vertices.clear();
    for(int i = 0; i< this->m_edges.size(); i++)
    {
        m_interface->m_main_box.remove_child(m_edges[i].m_interface->m_top_edge);
    }
    m_edges.clear();
    rest(500);
    charger_graphe("graphe_foret.txt");
  }
}

void Graph::ajouter_sommet(int idx)
{
    std::stringstream path;
    path << "graphe_" << m_identifiant << ".txt";
    add_interfaced_vertex(get_idx_ver_max()+1,m_vertices[idx].m_value,m_vertices[idx].m_interface->m_top_box.get_posx() + 10,
                          m_vertices[idx].m_interface->m_top_box.get_posy() + 10,m_vertices[idx].m_interface->m_img.get_pic_name(),
                          m_vertices[idx].m_interface->m_img.get_pic_idx());
    set_idx_ver_max(get_idx_ver_max()+1);
    std::fstream fic(path.str(), std::ios::in | std::ios::out ); // On ouvre un flux pour le fichier
    if(fic)
    {

        std::string name,chemin; //Nom et chemin jusqu'a l'image
        int idx_ver,idx_arete,x,y,ordre,nb_aretes,s1,s2; // Idx pour sommet et ar�te , coordonn�es x,y pour les sommets
        //le nombre d'ar�te pour les parcourir et s1 et s2 les sommets d'une ar�te
        float poids;
        double pop;
        fic >> m_identifiant;
        fic >> ordre;                                // Voir le fichier pour mieux comprendre la r�cup des donn�es.
        for(int i =0; i< ordre; i++)
        {
//            fic.ignore('-',':');
            fic >> name;
//            fic.ignore('-',':');
            fic >> idx_ver;
//            fic.ignore('-',':');
            fic >> pop;
//            fic.ignore('-',':');
            fic >> x;
//            fic.ignore('-',':');
            fic >> y;
//            fic.ignore('*','*');
            fic >> chemin;

        }

            fic >> nb_aretes;
            for(int j =0 ; j< nb_aretes ; j++)
            {
                fic >> idx_arete;
                fic >> s1;
                fic >> s2;
                fic >> poids;
                if(s1 == idx)
                {
                  add_interfaced_edge(get_idx_edge_max()+1,get_idx_ver_max(),s2,poids);
                  set_idx_edge_max(get_idx_edge_max()+1);
                }
                if(s2 == idx)
                {
                  add_interfaced_edge(get_idx_edge_max()+1,s1,get_idx_ver_max(),poids);
                  set_idx_edge_max(get_idx_edge_max()+1);
                }
            }
        fic.close();
        sauvegarder_graphe(path.str());
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
}
void Graph::supprimer_sommet(int idx)
{
  m_interface->m_main_box.remove_child(m_vertices[idx].m_interface->m_top_box);
  std::stringstream path;
  path << "graphe_" << m_identifiant << ".txt";
  std::fstream fic(path.str(), std::ios::in | std::ios::out ); // On ouvre un flux pour le fichier
  if(fic)
  {

      std::string name,chemin; //Nom et chemin jusqu'a l'image
      int idx_ver,idx_arete,x,y,ordre,nb_aretes,s1,s2; // Idx pour sommet et ar�te , coordonn�es x,y pour les sommets
      //le nombre d'ar�te pour les parcourir et s1 et s2 les sommets d'une ar�te
      float poids;
      double pop;
      fic >> m_identifiant;
      fic >> ordre;                                // Voir le fichier pour mieux comprendre la r�cup des donn�es.
      for(int i =0; i< ordre; i++)
      {
//            fic.ignore('-',':');
          fic >> name;
//            fic.ignore('-',':');
          fic >> idx_ver;
//            fic.ignore('-',':');
          fic >> pop;
//            fic.ignore('-',':');
          fic >> x;
//            fic.ignore('-',':');
          fic >> y;
//            fic.ignore('*','*');
          fic >> chemin;

      }

          fic >> nb_aretes;
          for(int j =0 ; j< nb_aretes ; j++)
          {
              fic >> idx_arete;
              fic >> s1;
              fic >> s2;
              fic >> poids;
              if(m_edges[j].m_to == idx )
              {
                m_interface->m_main_box.remove_child(m_edges[j].m_interface->m_top_edge);
                m_interface->m_main_box.remove_child(m_edges[j].m_interface->m_box_edge);
              }
              if(m_edges[j].m_from == idx)
              {
                m_interface->m_main_box.remove_child(m_edges[j].m_interface->m_top_edge);
                m_interface->m_main_box.remove_child(m_edges[j].m_interface->m_box_edge);
              }

          }
      fic.close();


}

}

void Graph::reset_color()
{
    for( int i = 0; i < m_vertices.size(); i++)
    {
        m_vertices[i].m_interface->m_top_box.set_bg_color(BLANC);
    }
}

void Graph::colorier_sommets()
{
    for(int i = 0; i < m_vertices.size(); i++ )
    {
      std::cout << m_vertices.size() << std::endl;
        if( m_vertices[i].get_color() == 1)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color(ROSE);
        }

        if( m_vertices[i].get_color() == 2)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color( BLEU );
        }

        if( m_vertices[i].get_color() == 3)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color( VERT );
        }

        if( m_vertices[i].get_color() == 4)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color( JAUNE );
        }

        if( m_vertices[i].get_color() == 5)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color( ROSECLAIR );
        }

        if( m_vertices[i].get_color() == 6)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color( BLEUCLAIR );
        }

        if( m_vertices[i].get_color() == 7)
        {
            m_vertices[i].m_interface->m_top_box.set_bg_color( VERTCLAIR );
            std::cout << " COLO7777" ;
        }
    }
}

///Algorithme de recherche d'une forte connexité et des connexités
void Graph::chercher_forte_connexite()
{

    int num = 1;
    int blabla = -1;
    bool condition1;

        int ordre = m_vertices.size();
        std::vector<int> v;
        std::stack<int> pile;
        int adjacence[ordre][ordre]; //matrice d'adjacence
        bool c1[ordre], c2[ordre]; //Tableau de connexite
        int x,y, c[ordre];  //Numeros de sommets intermediaires
        bool marque[ordre]; //Tableau de marquage

        bool ajoute = true;

        ///Remplissage du vecteur et des tableaux de connexite 0
        for(int i = 0; i < ordre ; i++)
        {
            v.push_back(0);
            c1[i] = false;
            c2[i] = false;
            c[i] = -1;
            marque[i] = false;
        }

        ///Initialisation de matrice de dimensions N*N avec toutes les cases nulles
        for( int i = 0; i < ordre ; i++)
        {
            for(int j = 0; j < ordre ; j++)
            {
                adjacence[i][j] = 0;
            }
        }

        ///Ajout des 1 la ou il y a des aretes
        for(auto i = m_edges.begin(); i!=m_edges.end(); i++)
        {
            adjacence[i->second.m_from][i->second.m_to] = 1;
        }

        ///Initialisation
        c1[m_vertices.begin()->first] = true;
        c2[m_vertices.begin()->first] = true;

        while(ajoute) /// Recherche des composantes connexes arrivant à ajoutées dans C1
        {
            ajoute = false;
            for( x= 0; x < ordre; x++)
            {
                if(!marque[x] && c1[x] == true)
                {
                    marque[x] = true;
                    for(y = 0; y <ordre; y++)
                    {
                        if(adjacence[x][y] == 1 && !marque[y])
                        {
                            c1[y]=true;
                            ajoute = true;
                        }//fin if
                    }//fin for
                }//fin if
            }//fin for

        }

        ///Remplissage du vecteur et des tableaux de connexite 0
        for(int i = 0; i < ordre ; i++)
        {
            marque[i] = false;
        }

        c2[m_vertices.end()->first] = true;
        ajoute = true;
        while(ajoute) ///Recherche des composantes connexes partant de S ajoutées dans c2
        {
            ajoute = false;
            for( x= ordre -1; x != -1; x--)
            {
                if(!marque[x] && c2[x] ==  true)
                {
                    marque[x] = true;
                    for(y = ordre; y != 0; y --)
                    {
                        if(adjacence[x][y] == 1 && !marque[y])
                        {
                            c2[y]=1;
                            ajoute = true;
                        }//fin if
                    }//fin for
                }//fin if
            }//fin for

        }

        for( x=0; x<ordre; x++)
        {
            if(c1[x] == true && c2[x] == true)
            {
                c[x] = x;
                m_vertices[x].set_color(num);
            }
        }

    ///Trouver les autres composantes connexes
    do
    {
        ajoute = false;
        num++;
        for( int i = 0; i < m_vertices.size(); i++)
        {
            if(marque[i] == false)
            {
                blabla = i;
                condition1 = true;
                ajoute = true;
                break;
            }
        }
        marque[blabla] = true;
        m_vertices[blabla].set_color(num);
        while(condition1)
        {
            condition1 = false;
            for(int i = 0; i <ordre; i++)
            {
                if(adjacence[blabla][i] && !marque[i])
                {
                    condition1 = true;
                    m_vertices[i].set_color(num);
                }
            }
        }
    }while(ajoute);

    colorier_sommets(); ///Colorier les différents sommets
    std::cout << "caca" << std::endl;
}
