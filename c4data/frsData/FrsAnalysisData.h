#ifndef FrsAnalysisData_H
#define FrsAnalysisData_H

#include "TObject.h"
#include "../../config/setup.h"

class FrsAnalysisData : public TObject
{
    public:
        FrsAnalysisData();

        //FrsAnalysisData(/*overload*/);

        ~FrsAnalysisData();

        // Getters
        /*inline Bool_t Get_ZvsAoQ_gate(int gate) { return fZvsAoQ_gates[gate]; }
        inline Bool_t Get_ZvsZ2_gate(int gate) { return fZvsZ2_gates[gate]; }
        inline Bool_t Get_x2vsAoQ_gate(int gate) { return fx2vsAoQ_gates[gate]; }
        inline Bool_t Get_x4vsAoQ_gate(int gate) { return fx4vsAoQ_gates[gate]; }
        inline Bool_t Get_ZvsdEdeg_gate(int gate) { return fZvsdEdeg_gates[gate]; }
        inline Bool_t Get_ZvsAoQ_mhtdc_gate(int gate) { return fZvsAoQ_mhtdc_gates[gate]; }
        inline Bool_t Get_ZvsZ2_mhtdc_gate(int gate) { return fZvsZ2_mhtdc_gates[gate]; }
        inline Bool_t Get_x2vsAoQ_mhtdc_gate(int gate) { return fx2vsAoQ_mhtdc_gates[gate]; }
        inline Bool_t Get_x4vsAoQ_mhtdc_gate(int gate) { return fx4vsAoQ_mhtdc_gates[gate]; }
        inline Bool_t Get_ZvsdEdeg_mhtdc_gate(int gate) { return fZvsdEdeg_mhtdc_gates[gate]; }*/

        // Setters
        /*inline void Set_ZvsAoQ_gates(int gate, Bool_t pass) { fZvsAoQ_gates[gate] = pass; }
        inline void Set_ZvsZ2_gates(int gate, Bool_t pass) { fZvsZ2_gates[gate] = pass; }
        inline void Set_x2vsAoQ_gates(int gate, Bool_t pass) { fx2vsAoQ_gates[gate] = pass; }
        inline void Set_x4vsAoQ_gates(int gate, Bool_t pass) { fx4vsAoQ_gates[gate] = pass; }
        inline void Set_ZvsdEdeg_gates(int gate, Bool_t pass) { fZvsdEdeg_gates[gate] = pass; }
        inline void Set_ZvsAoQ_mhtdc_gates(int gate, Bool_t pass) { fZvsAoQ_mhtdc_gates[gate] = pass; }
        inline void Set_ZvsZ2_mhtdc_gates(int gate, Bool_t pass) { fZvsZ2_mhtdc_gates[gate] = pass; }
        inline void Set_x2vsAoQ_mhtdc_gates(int gate, Bool_t pass) { fx2vsAoQ_mhtdc_gates[gate] = pass; }
        inline void Set_x4vsAoQ_mhtdc_gates(int gate, Bool_t pass) { fx4vsAoQ_mhtdc_gates[gate] = pass; }
        inline void Set_ZvsdEdeg_mhtdc_gates(int gate, Bool_t pass) { fZvsdEdeg_mhtdc_gates[gate] = pass; }*/

    private:

        /*Bool_t fZvsAoQ_gates[FRS_GATES] = {false};
        Bool_t fZvsZ2_gates[FRS_GATES] = {false};
        Bool_t fx2vsAoQ_gates[FRS_GATES] = {false};
        Bool_t fx4vsAoQ_gates[FRS_GATES] = {false};
        Bool_t fZvsdEdeg_gates[FRS_GATES] = {false};
        Bool_t fZvsAoQ_mhtdc_gates[FRS_GATES] = {false};
        Bool_t fZvsZ2_mhtdc_gates[FRS_GATES] = {false};
        Bool_t fx2vsAoQ_mhtdc_gates[FRS_GATES] = {false};
        Bool_t fx4vsAoQ_mhtdc_gates[FRS_GATES] = {false};
        Bool_t fZvsdEdeg_mhtdc_gates[FRS_GATES] = {false};*/

    public:
        ClassDef(FrsAnalysisData, 1)

};


#endif