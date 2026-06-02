#ifndef ATIMA_H
#define ATIMA_H
#include "catima/catima.h"
#include "../c4data/frsData/TFrsConfiguration.h"

#include "Rtypes.h"
#include <array>
#include <vector>

class TFrsConfiguration;

class Atima
{
    public:
        Atima();
        ~Atima() {};

        void AddLayer(catima::Material m);
        void ClearStack() { shiyan_s1s2.clear(); }

        void Calculate(); // use default or pre-set projectile/target
        void Calculate(catima::Projectile p, catima::Material t, Float_t e);

        void DefineProjectile(catima::Projectile p) { projectile = p; }
        void DefineTarget(catima::Material t) { target = t; }

        void BuildMaterial();

        std::pair<Float_t, Float_t> CalculateEnergyLoss(const catima::Projectile& proj, Float_t E_initial);

        catima::Projectile projectile;
        catima::Material target;

        Double_t E; // MeV per nucleon
        std::vector<catima::Material> shiyan_s1s2;
        std::vector<catima::Material> pareeksha_s1s2;

        TFrsConfiguration const* frs_config; //private?

    
};

class Material : public catima::Material
{
    public:
        Material(std::initializer_list<std::array<Double_t, 3>>list) : catima::Material(list) {}; // A, Z, Stoich#
        Material(std::initializer_list<std::array<Double_t, 3>>list, Double_t d) : catima::Material(list) { this->density(d); } // input optional density
        Material(std::initializer_list<std::array<Double_t, 3>>list, Double_t d, Double_t t) : catima::Material(list) { this->density(d).thickness(t); } // input optional density, thickness
};

class Projectile : public catima::Projectile
{
    public:
        Projectile(Double_t a, Double_t z) : catima::Projectile(a, z) {}; // A, Z
};


#endif

