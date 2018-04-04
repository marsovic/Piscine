#include "espece.h"

espece::espece()
{
    //ctor
}

espece::~espece()
{
    //dtor
}

void espece::set_regime(int regime, int quantite)
{
    m_regime.insert(std::pair<int,int>(regime,quantite));
}

void espece::set_produit(int produit, int quantite)
{
    m_regime.insert(std::pair<int,int>(produit,quantite));
}

///Afficher les informations sur une espèce
void espece::display()
{
    std::cout << "Nom : " << m_nom << "."<< std::endl;

    std::cout << "Regime alimentaire : ";
    for(const auto& elem : m_regime)
    {
        std::cout << elem.first << ", ";
    }
    std::cout << "." <<std::endl;

    std::cout << "Predateurs : ";
    for(unsigned int i=0; i< m_predateurs.size();i++)
    {
        std::cout << m_predateurs.at(i).get_nom() << ", ";
    }
    std::cout << "." << std::endl;

    std::cout << "Proies : ";
    for(unsigned int i=0; i< m_proies.size();i++)
    {
        std::cout << m_proies.at(i).get_nom() << ", ";
    }
    std::cout << "." << std::endl;

    std::cout << "Elements produits : ";
    for(const auto& elem : m_produit)
    {
        std::cout << elem.first << ", ";
    }
    std::cout << "." <<std::endl;

    std::cout << "Nombre d'individus : " << m_population << "." << std::endl;
}

///Ajouter une espèce
void espece::ajouter()
{
    bool test = false;
    std::string nom, esp;
    int pop, regime, produit, quantite, nb;
    std::cout << "Ajout d'une nouvelle espece : " << std::endl;

    std::cout << "Saisir nom : ";
    std::cin >> nom;
    set_nom(nom);
    std::cout << std::endl;

    std::cout << "Saisir le nombre de regime(s) alimentaire(s) : ";
    std::cin >> nb;
    for(unsigned int i = 0; i < nb; i++)
    {
        std::cout << "Saisir Regime alimentaire numero " << i+1 <<"  (1:    ,2:   ,3:    ): ";
        std::cin >> regime; std::cout << std::endl;
        std::cout << "Saisissez la quantite consommee : ";
        std::cin >> quantite; std::cout << std::endl;
        set_regime(regime, quantite);
    }

    std::cout << "Saisir le nombre de predateur(s) : ";
    std::cin >> nb;
    std::cout << "Predateurs : ";
    /*for(unsigned int i=0; i< nb;i++)
    {
        std::cout << "Saisir le predateurs numero " << i+1 << ": ";
        std::cin >> esp;
        for(const auto& elem: m_nom)           /// ESPECE A MODIFIER UNE FOIS QUE LA LISTE ENTIERE DES ESPECES DE GRAPHE EST OK
        {
            nom = elem;
            if(nom == esp)
            {
                ;
                test = true
                break;
            }
        }
        if(test == false)
        {
            std::cout << "Predateur non trouve. ASTUCE : Pensez à l'enregistrer! " << std::endl;
        }
        else
            test = false;
    }

    std::cout << "Saisir le nombre de proie(s) : ";
    std::cin >> nb;
    std::cout << "Proie(s) : ";
    for(unsigned int i=0; i< nb;i++)
    {
        std::cout << "Saisir la proie numero " << i+1 << ": ";
        std::cin >> esp;
        for(const auto& elem: espece)           /// ESPECE A MODIFIER UNE FOIS QUE LA LISTE ENTIERE DES ESPECES DE GRAPHE EST OK
        {
            if(espece.get_nom() == esp)
            {
                set_proies(elem);
                test = true
                break;
            }
        }
        if(test == false)
        {
            std::cout << "Proie non trouve. ASTUCE : Pensez à l'enregistrer! " << std::endl;
        }
        else
            test = false;
    }

    std::cout << "Saisir le nombre d'element(s) produit(s) : ";
    std::cin >> nb;
    for(unsigned int i = 0; i < nb; i++)
    {
        std::cout << "Saisir l'element produit numero " << i+1 <<"  (1:    ,2:   ,3:    ): ";
        std::cin >> produit; std::cout << std::endl;
        std::cout << "Saisissez la quantite produite : "
        std::cin >> quantite; std::cout << std::endl;
        set_produit(produit, quantite);
    }
*/
    std::cout << "Saisissez le nombre d'individus de l'espece : ";
    std::cin >> quantite;
    set_population(quantite);

    std::cout << std::endl << "Votre espece est crée!" << std::endl;

}

void espece::supprimer()
{
    //Supprimer directement dans le graphe l'espece du vecteur d'espece
}
