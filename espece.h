#ifndef ESPECE_H
#define ESPECE_H
#include "iostream"
#include <map>
#include <vector>


class espece
{
    private:
        std::string m_nom;

        ///First : nom du regime & Second : quantit� en kg mang� pour un individu
        std::map<int, int> m_regime;

        ///First : nom des matieres produites & Second : quantit� en kg
        std::map<int, int> m_produit;

        /// Vecteur de proies + ressources (du r�gime si non Espece)
        std::vector<espece> m_proies;

        ///Vecteur de pr�dateurs
        std::vector<espece> m_predateurs;

        int m_population;

        //bitmap bmp;


    public:
        ///Constructeur & Destructeur
        espece();
        ~espece();

        ///Getters & Setters
        std::string get_nom()                           { return m_nom; }
        std::map<int,int> get_regime() const            { return m_regime; }
        std::map<int, int> get_produit() const          { return m_produit; }
        std::vector<espece> get_proies() const          { return m_proies; }
        std::vector<espece> get_predateurs() const      { return m_predateurs; }
        int get_population()                            { return m_population; }

        void set_nom(std::string nom)                   { m_nom = nom; }
        void set_regime(int regime, int quantite);
        void set_produit(int produit, int quantite);
        void set_predateurs(espece e)                   { m_predateurs.push_back(e); }
        void set_proies(espece e)                       { m_proies.push_back(e); }
        void set_population(int pop)                    { m_population = pop; }

        ///M�thodes
        void display();
        void ajouter();
        void supprimer();
};

#endif // ESPECE_H
