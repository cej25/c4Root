#include "Atima.h"
#include <numeric>
#include <iostream>


Atima::Atima()
{
    
};


void Atima::Calculate(catima::Projectile p, catima::Material t, Double_t e)
{
    auto result = catima::calculate(p, t, e);
    std::cout << "E (MeV/u) = " << e << ", dEdx1 = " << result.dEdxi << " MeV/g/cm2" << std::endl;

    return;
	
};