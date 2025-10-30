#include "Atima.h"
#include <numeric>
#include <iostream>
#include <iomanip>


Atima::Atima()
{
    BuildMaterial();
    frs_config = TFrsConfiguration::GetInstance();
};

void Atima::AddLayer(catima::Material m)
{
    shiyan_s1s2.push_back(m); 
    //pareeksha_s1s2.push_back(m);
}

void Atima::Calculate(catima::Projectile p, catima::Material t, Double_t e)
{
    auto result = catima::calculate(p, t, e);
    //std::cout << "E (MeV/u) = " << e << ", dEdx1 = " << result.dEdxi << " MeV/g/cm2" << std::endl;

    return;
	
};

// Build Material from SCI21 until just before LISA layer 1 -- Shiyan
void Atima::BuildMaterial()
{
    ClearStack();

    // SCI21 - EJ230
    AddLayer(Material({{1,1,10}, {6,6,9}}, 1.032, 0.1416936));
    // TPC22 pocket Ti
    AddLayer(Material({{48,22,1}}, 4.519, 0.09038));
    // TPC22 gas 
    AddLayer(catima::get_compound(catima::material::P10).density(0.00159).thickness(0.0141));
    // Degrader Al
    /*if(frs_config->degrader_in == true)*/AddLayer(Material({{27,13,1}}, 2.702, 0.735));
    // Vacuum Window Fe
    AddLayer(Material({{56,26,1}}, 7.866, 0.07866));
    // Air
    AddLayer(catima::get_compound(catima::material::Air).density(0.001205).thickness(0.02169));
    // TPC23 windows
    AddLayer(catima::get_compound(catima::material::Mylar).density(1.39).thickness(0.00709676));
    // TPC23 gas
    AddLayer(catima::get_compound(catima::material::P10).density(0.00159).thickness(0.0141));
    // Air
    AddLayer(catima::get_compound(catima::material::Air).density(0.001205).thickness(0.0150625));
    // Music21 windows 
    AddLayer(catima::get_compound(catima::material::Kapton).density(1.42).thickness(0.000639));
    // Music21 gas
    AddLayer(catima::get_compound(catima::material::P10).density(0.00159).thickness(0.06042));
    // Air
    AddLayer(catima::get_compound(catima::material::Air).density(0.001205).thickness(0.008676));
    // LISA window Ti
    AddLayer(Material({{48,22,1}}, 4.519, 0.009038)); 

    // === Print summary only once ===
    static bool printed = false;
    if (!printed) 
    {
        printed = true;

        std::vector<std::string> names = {
            "SCI21", "TPC22 pocket", "TPC22 gas", "Degrader", "Vacuum window",
            "Air #1", "TPC23 windows", "TPC23 gas", "Air #2",
            "MUSIC21 windows", "MUSIC21 gas", "Air #3", "LISA window"
        };

        std::cout << "\n===== Shiyan S1-S2 Material Stack =====" << std::endl;
        std::cout << std::left
                << std::setw(20) << "Material"
                << std::setw(15) << "Thickness [g/cm²]"
                << std::setw(15) << "Density [g/cm³]"
                << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;

        for(size_t i = 0; i < shiyan_s1s2.size(); ++i)
        {
            const auto& m = shiyan_s1s2[i];
            std::cout << std::left
                      << std::setw(20) << names[i]
                      << std::setw(15) << m.thickness()
                      << std::setw(15) << m.density()
                      << std::endl;
        }
        std::cout << "------------------------------------------------------------\n";
    }

}

// Calculate Energy Loss in ShiyanMaterial
Double_t Atima::CalculateEnergyLoss(const catima::Projectile& proj, Double_t E_initial)
{
    Double_t E_in = E_initial;
    Double_t total_loss = 0.0;

    std::vector<std::string> names = {
        "SCI21","TPC22 pocket","TPC22 gas","Degrader","Vacuum window",
        "Air #1","TPC23 windows","TPC23 gas","Air #2",
        "MUSIC21 windows","MUSIC21 gas","Air #3","LISA window"
    };

    std::cout << "\n=== Energy loss through Shiyan stack ===\n";
    std::cout << std::left
              << std::setw(20) << "Layer"
              << std::setw(15) << "E_in [MeV/u]"
              << std::setw(15) << "E_out [MeV/u]"
              << std::setw(15) << "ΔE [MeV/u]" << std::endl;
    std::cout << "---------------------------------------------------------------\n";

    for(size_t i = 0; i < shiyan_s1s2.size(); ++i)
    {
        catima::Material m = shiyan_s1s2[i]; // copy material with thickness
        auto result = catima::calculate(proj, m, E_in);
        Double_t E_out = result.Eout;
        Double_t dE = E_in - E_out;

        std::cout << std::left
                  << std::setw(20) << names[i]
                  << std::setw(15) << E_in
                  << std::setw(15) << E_out
                  << std::setw(15) << dE << std::endl;

        total_loss += dE;
        E_in = E_out;
    }

    std::cout << "---------------------------------------------------------------\n";
    std::cout << "Total ΔE = " << total_loss << " MeV/u, Final E = " << E_in << " MeV/u\n";
    std::cout << "===============================================================\n";

    return total_loss;
}

// maybe do something like this for vector
// std::vector<Double_t> Atima::BatchCalculateLoss(const std::vector<catima::Projectile>& projs, const catima::Material& mat, const std::vector<Double_t>& Eins)
// {
//     std::vector<Double_t> losses;
//     losses.reserve(Eins.size());
//     for(size_t i=0; i<Eins.size(); ++i) {
//         auto res = catima::calculate(projs[i], mat, Eins[i]);
//         Double_t dE = Eins[i] - res.Eout; //but take energy out instead of dE
//         losses.push_back(dE);
//     }
//     return losses;
// }

// // Build Material from SCI21 until just before LISA layer 1 -- Pareeksha
// void Atima::BuildMaterial()
// {
//     ClearStack();

//     AddLayer(EJ230.density(1.032).thickness(0.1032));
//     AddLayer(Ti);
//     AddLayer(catima::get_compound(catima::material::P10).density(1.0).thickness(0.0141));
//     /*if(frs_config->degrader_in == true)*/AddLayer(Al.density(2.702).thickness(0.7302));
//     AddLayer(Fe);
//     AddLayer(catima::get_compound(catima::material::Air).density(1.0).thickness(0.01205));
//     AddLayer(EJ230.density(1.105).thickness(0.1055275));
//     AddLayer(catima::get_compound(catima::material::Mylar).density(1.0).thickness(0.015367));
//     AddLayer(catima::get_compound(catima::material::Air).density(1.0).thickness(0.01205));
//     AddLayer(catima::get_compound(catima::material::Mylar).density(1.0).thickness(0.00709676));
//     AddLayer(catima::get_compound(catima::material::P10).density(1.0).thickness(0.0141));
//     AddLayer(catima::get_compound(catima::material::Air).density(1.0).thickness(0.017111));
//     AddLayer(catima::get_compound(catima::material::Kapton).density(1.42).thickness(0.000639));
//     AddLayer(catima::get_compound(catima::material::P10).density(1.0).thickness(0.06042));
//     AddLayer(catima::get_compound(catima::material::Air).density(1.0).thickness(0.00723));
//     AddLayer(Ti.density(4.519).thickness(0.0094732249));

// }



// Material::Material(std::initializer_list<std::array<Double_t, 3>> list)
// {
//     catima::Material mat(list);


// };

/*
extern "C"
{
    void calculate_(double* proj,
                    int* pn,
                    double* ein,
                    double* targ,
                    int* nnuca,
                    int* tm,
                    double* rhoa,
                    int* igasa,
                    double* thick,
                    double* eout,
                    double* range,
                    double* dedxi,
                    double* dedxo,
                    double* remra,
                    double* rstr,
                    double* estr,
                    double* astr,
                    double* tof,
                    double* intrthick)
}

namespace Atima
{
    const TargetMaterial TargetMaterial::Air = TargetMaterial({MaterialCompound(14, 7, 0.755267), 
                                                                MaterialCompound(16, 8, 0.231781),
                                                                MaterialCompound(39.948, 18, 0.012827),
                                                                MaterialCompound(12, 6, 0.000124)},
                                                                0.0012, kTRUE);
    
    const TargetMaterial TargetMaterial::LH2 = TargetMaterial({MaterialCompound(1, 1)}, 0.0708, kFALSE);
    const TargetMaterial TargetMaterial::Si = TargetMaterial({MaterialCompound(28, 14)}, 2.336, kFALSE);
    const TargetMaterial TargetMaterial::BC400 = TargetMaterial({MaterialCompound(1, 1, 0.085292), 
                                                                MaterialCompound(12, 6, 0.914708),
                                                                1.032, kFALSE});


    TransportResult Calculate(Double_t projMass_u,
                            Double_t projCharge_e,
                            Double_t projEnergy_MeV_per_u,
                            const TargetMaterial& targetMaterial,
                            Double_t tarThickness_mg_per_cm2)
    {
        TransportResult res;

        const auto invTotRatio = std::accumulate(
            targetMaterial.Compounds.begin(), targetMaterial.Compounds.end(),
            0., [](const Double_t sum, const MaterialCompound& comp) -> Double_t { return sum + comp.Ratio; });

        Int_t tcompsize = 3, tcompnum = targetMaterial.Compounds.size(), pn = 2;
        std::vector<Double_t> tarFortran;
        tarFortran.resize(tcompnum * tcompsize);
        for (int i = 0; i < tcompnum; i++)
        {
            tarFortran[i + tcompnum * 0] = targetMaterial.Compounds[i].Mass_u;
            tarFortran[i + tcompnum * 1] = targetMaterial.Compounds[i].Charge_e;
            tarFortran[i + tcompnum * 2] = targetMaterial.Compounds[i].Ratio * invTotRatio;
        }

        calculate_(proj,
                   &pn,
                   &projEnergy_MeV_per_u,
                   &tarFortran[0],
                   &tcompnum,
                   &tcompsize,
                   &density,
                   &tGas,
                   &tarThickness_mg_per_cm2,
                   &res.EnergyOut_MeV_per_u,
                   &res.Range_mg_per_cm2,
                   &res.dEdXIn_MeVcm2_per_mg,
                   &res.dEdXOut_MeVcm2_per_mg,
                   &res.RemainingRange_mg_per_cm2,
                   &res.RangeStrag_mg_per_cm2,
                   &res.EStrag_MeV_per_u,
                   &res.AngStrag_mRad,
                   &res.ToF_ns,
                   &res.InterpolatedTargetThickness);

        res.EnergyIn_MeV_per_u = projEnergy_MeV_per_u;
        res.EStrag_MeV_per_u *= res.dEdXOut_MeVcm2_per_mg;
        res.ELoss_MeV_per_u = res.EnergyIn_MeV_per_u - res.EnergyOut_MeV_per_u;
        res.AngStrag_mRad *= 1e3;
        res.dEdXIn_MeVcm2_per_mg *= projMass_u;
        res.dEdXOut_MeVcm2_per_mg *= projMass_u;
        return res;

    }

    TransportResult Calculate_mm(Double_t projMass_u,
                                 Double_t projCharge_e,
                                 Double_t projEnergy_MeV_per_u,
                                 const TargetMaterial& targetMaterial,
                                 Double_t tarThickness_mm)
    {
        return Calculate(projMass_u,
                         projCharge_e,
                         projEnergy_MeV_per_u,
                         targetMaterial,
                         targetMaterial.Density * tarThickness_mm * 100);
    }
}
*/
