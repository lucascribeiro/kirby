#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

class GameObject
{
private:
    int hp;
    int mp;
    int class;
    Sprite *graphicalRep;
    Collision *geometry;

public:
    GameObject();
    /// ....
    virtual ~GameObject();
};


#endif // GAMEOBJECT_H_INCLUDED
