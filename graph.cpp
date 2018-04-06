#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

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
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
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

    //Label Arête
    m_tool_box.add_child(m_label_arete);
    m_label_arete.set_frame(3,465,40,40);
    m_label_arete.set_message("Arete :");

    //Bouton Ajouter_Arête
    m_tool_box.add_child(m_bouton_add_edge);
    m_bouton_add_edge.set_frame(3,485,80,80);
    m_bouton_add_edge.set_bg_color(CYAN);
    m_bouton_add_edge.add_child(m_bouton_add_edge_label);
    m_bouton_add_edge_label.set_message("Ajouter");

    //Bouton Supprimer_Arête
    m_tool_box.add_child(m_bouton_del_edge);
    m_bouton_del_edge.set_frame(3,575,80,80);
    m_bouton_del_edge.set_bg_color(ORANGECLAIR);
    m_bouton_del_edge.add_child(m_bouton_del_edge_label);
    m_bouton_del_edge_label.set_message("Supprimer");
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
}

void Graph::charger_graphe(std::string fichier)//Fichier est le nom du fichier dans le dossier du projet(Ex : "graphe_terre.txt")
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600); //Initialisation de l'interface de graphe !
    std::fstream fic(fichier, std::ios::in | std::ios::out ); // On ouvre un flux pour le fichier
    if(fic)
    {

        std::string name,chemin; //Nom et chemin jusqu'a l'image
        int idx,idx_arete,x,y,ordre,nb_aretes,s1,s2; // Idx pour sommet et ar�te , coordonn�es x,y pour les sommets
        double pop;                                  //le nombre d'ar�te pour les parcourir et s1 et s2 les sommets d'une ar�te
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

            fic >> nb_aretes;
            for(int j =0 ; j< nb_aretes ; j++)
            {
                fic >> idx_arete;
                fic >> s1;
                fic >> s2;
                add_interfaced_edge(idx_arete,s1,s2,0.0); // Cette m�thode ajoute une ar�te � la map m_edges et l'affiche.
            }


        fic.close();

    }

    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
}

void Graph::changer_graphe()
{
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
    charger_graphe("graphe_terre.txt");
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
    charger_graphe("graphe_test.txt");
  }

  if(this->m_interface->m_bouton_graph3.clicked())
  //Bouton graphe3 , voir graph.h dans GraphInterface !
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
    charger_graphe("graphe_existepas.txt");
  }
}
