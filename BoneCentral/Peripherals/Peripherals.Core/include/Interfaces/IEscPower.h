#ifndef IESCPOWER_H
#define IESCPOWER_H

class IEscPower
{
    public:
        virtual void turnOnEscs() = 0;
        virtual void turnOffEscs() = 0;
};

#endif
