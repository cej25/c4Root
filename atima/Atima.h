#ifndef ATIMA_H
#define ATIMA_H
#include "catima/catima.h"

#include "Rtypes.h"
#include <array>
#include <vector>

class Atima
{
    public:
        Atima();
        ~Atima() {};

        void Calculate(); // use default or pre-set projectile/target
        void Calculate(catima::Projectile p, catima::Material t, Double_t e); // input newly created materials from external Task
        void DefineProjectile(catima::Projectile p) { projectile = p; }
        void DefineTarget(catima::Material t) { target = t; }

        catima::Projectile projectile;
        catima::Material target;
        Double_t E; // MeV per nucleon
    
};

class Material : public catima::Material
{
    public:
        Material(std::initializer_list<std::array<Double_t, 3>>list) : catima::Material(list) {}; // A, Z, not sure what 3rd is
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

Projectile carbon(2, 6);


#endif

