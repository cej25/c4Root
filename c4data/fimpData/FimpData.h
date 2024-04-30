#ifndef FimpData_H
#define FimpData_H


class FimpItem : public TObject
{
    public:
        FimpItem();

        void SetAll();
        void Reset();

        ClassDefNV(FimpItem, 2);
    
    private:
        // members
};


#endif