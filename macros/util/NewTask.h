#ifndef NewTask_H
#define NewTask_H

class NewTask : public FairTask
{
    public:
        NewTask();
        NewTask(const TString& name, Int_t verbose);

        ~NewTask();

        // Upon Task initiation
        virtual InitStatus Init();

        // Once per event
        void Exec(Option_t* option);

        // Once per event, after Exec
        void FinishEvent();

        // Upon Task complete
        void FinishTask();



        // Add methods


    private:

        // Initialise data structures and variables

    public:
        ClassDef(NewTask, 1);
};

#endif

