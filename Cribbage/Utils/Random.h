#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random
{

    static Random* sSingleton;
    Random();
    ~Random();

public:

    static Random* Instance();

    void destroy() { delete this; }
    
    int randInt(int modulo = -1);

};

#endif
