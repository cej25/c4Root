#ifndef ATIMA_H
#define ATIMA_H
#include "catima/catima.h"
#include "../c4data/frsData/TFrsConfiguration.h"

#include "Rtypes.h"
#include <array>
#include <vector>

class TFrsConfiguration;

struct Layer
{
    catima::Material material;
    Double_t thickness; //g/cm2
};

class Atima
{
    public:
        Atima();
        ~Atima() {};

        void AddLayerShiyan(catima::Material m, Double_t thickness)  { shiyan_s1s2.push_back({m, thickness}); }
        void ClearShiyan() { shiyan_s1s2.clear(); }

        void AddLayerPareeksha(catima::Material m, Double_t thickness)  { pareeksha_s1s2.push_back({m, thickness}); }
        void ClearPareeksha() { pareeksha_s1s2.clear(); }

        void Calculate(); // use default or pre-set projectile/target
        void Calculate(catima::Projectile p, catima::Material t, Double_t e); // input newly created materials from external Task
        
        void DefineProjectile(catima::Projectile p) { projectile = p; }
        void DefineTarget(catima::Material t) { target = t; }

        void BuildShiyanMaterial();
        void BuildPareekshaMaterial();

        Double_t CalculateEnergyLossShiyan(const catima::Projectile& proj, Double_t E_initial);



        catima::Projectile projectile;
        catima::Material target;

        Double_t E; // MeV per nucleon
        std::vector<Layer> shiyan_s1s2;
        std::vector<Layer> pareeksha_s1s2;

        TFrsConfiguration const* frs_config; //private?)

    
};

class Material : public catima::Material
{
    public:
        Material(std::initializer_list<std::array<Double_t, 3>>list) : catima::Material(list) {}; // A, Z, stoichiometric
        Material(std::initializer_list<std::array<Double_t, 3>>list, Double_t d) : catima::Material(list) { this->density(d); } // input optional density
        Material(std::initializer_list<std::array<Double_t, 3>>list, Double_t d, Double_t t) : catima::Material(list) { this->density(d).thickness(t); } // input optional density, thickness
};

class Projectile : public catima::Projectile
{
    public:
        Projectile(Double_t a, Double_t z) : catima::Projectile(a, z) {}; // A, Z
};


// Materials library
Material water({
    {1, 1, 2},
    {16, 8, 1}},
    1.0,
    2.0);

Material EJ230({
    {1,1,10},
    {6,6,9}});

Material Ti({
    {48, 22, 1}},
    4.519);  

Material Al({
    {27,13,1}},
    2.702);

Material Fe({
    {56,26,1}},
    7.866);


Projectile carbon(12, 6);


#endif

