#ifndef KLASSENMITGLIED_H
#define KLASSENMITGLIED_H


class Klassenmitglied
{
private:
    int id = -1;
public:
    Klassenmitglied();  //Konstruktor, welcher ein leeres Objekt erstellt
    Klassenmitglied(int id);    //Konstruktor, welcher ein Klassenmitgliedobjekt erstellt mit ID
    int getId();    //Get-Methode für die ID
    void setId(int id);     //Set-Methode für die ID
};

#endif // KLASSENMITGLIED_H
