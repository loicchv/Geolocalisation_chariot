#ifndef LIAISONESP32_H
#define LIAISONESP32_H

#include <MKRWAN.h> 

class liaisonESP32{
    private:
        String data;
    public:
        liaisonESP32();
        void initialiser();
        String readData();
};
#endif