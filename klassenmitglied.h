#ifndef KLASSENMITGLIED_H
#define KLASSENMITGLIED_H


class Klassenmitglied
{
private:
    int id = -1;
public:
    Klassenmitglied();
    Klassenmitglied(int id);
    int getId();
    void setId(int id);
};

#endif // KLASSENMITGLIED_H
