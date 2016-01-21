/*
 * PWM.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: TekuConcept
 */

#include "PWM/PWM.h"

PWM::PWM(uint _addr_, short block) :
    block_(block),
    addr(_addr_), period(0), dutyA(0), dutyB(0),
    cdiv(1), polA(0), polB(0)
{
    // -- Working Configuration Values --
    addr.write(PWM_TBCTL , 0x00010100);
    addr.write(PWM_TBPHS , 0x00000000);
    addr.write(PWM_CMPCTL, 0x00000000);

    // Stop PWM Submodule and Reset Registers to default
    stop();
    setPolarityA(0);
    setPolarityB(0);
    setDutyA(0);
    setDutyB(0);
    setPeriod(500000);
}



PWM::~PWM()
{
}

void PWM::Initialize() {};


void PWM::start()
{
    uint tbctl  = addr.read(PWM_TBCTL) & 0xFFFF2FFF; // Mask: 0x0000FFFF
    uint aqsfrc = addr.read(PWM_AQSFRC)& 0x0000FFFF; // Mask: 0xFFFF0000

    // FREE,SOFT = 3
    tbctl |= (3<<14);
    // RLDCSF = 0
    //uint aqsfrc = 0; // Mask: 0xFFFF0000
    // CSFB = 0, CSFA = 0
    uint aqcsfrc= 0; // Mask: 0x0000FFFF

    addr.write(PWM_TBCTL, tbctl);
    addr.write(PWM_AQSFRC, aqsfrc);
    addr.write(PWM_AQCSFRC, aqcsfrc);
}



void PWM::stop()
{
    // since PWM stores two tags in one register
    // the mask is used to separate the left tag from the right tag
    uint tbctl  = addr.read(PWM_TBCTL);
    uint aqsfrc = 0;
    uint aqcsfrc= 0;

    // FREE,SOFT = 0
    tbctl &= 0xFFFF2FFF;
    // RLDCSF = 3
    aqsfrc |= ((3<<6) << 16);
    // CSFB = 1, CSFA = 1
    aqcsfrc |= ((1<<2) | 1);

    addr.write(PWM_TBCTL, tbctl);
    addr.write(PWM_AQSFRC, aqsfrc);
    addr.write(PWM_AQCSFRC, aqcsfrc);
}



int PWM::setPeriod(uint ns)
{
    if (ns < dutyA || ns < dutyB)
        return -1;
    period = ns;

    uint prd = ns / 10;
    uint cidx = 0; // division index
    cdiv = 1;      // clock divider
    if (prd > 0xFFFF)
    {
        for (uint i = 0; i <= 7; i++)
        {
            uint n = (i + 1) * 2;
            if ((prd / n) <= 0xFFFF)
            {
                cdiv = n;
                cidx = i + 1;
                break;
            }
        }
    }

    // clear clock divider
    uint tbctl = addr.read(PWM_TBCTL) & 0xFFFFFC7F;
    uint tbprd = addr.read(PWM_TBPRD) & 0x0000FFFF;
    // set new clock divider: HSPCLKDIV = cidx
    tbctl |= (cidx << 7);
    tbprd |= (((prd / cdiv) & 0x0000FFFF) << 16);
    addr.write(PWM_TBCTL, tbctl);
    addr.write(PWM_TBPRD, tbprd);

    return 0;
}

void PWM::Thrust(int powerLevel) {
    block_ == 0 ? setDutyA(powerLevel) : setDutyB(powerLevel);
}

int PWM::setDutyA(uint ns)
{
    if (ns > period)
        return -1;
    dutyA = ns;

    // Mask: 0xFFFF0000 + clear left
    uint dty = ns / 10;
    uint cmpa = addr.read(PWM_CMPA) & 0x0000FFFF;
    cmpa |= ((dty / cdiv) << 16);
    addr.write(PWM_CMPA, cmpa);

    return 0;
}

int PWM::setDutyB(uint ns)
{
    if (ns > period)
        return -1;
    dutyB = ns;

    // Mask: 0x0000FFFF + clear right
    uint dty = ns / 10;
    uint cmpb = addr.read(PWM_CMPB) & 0xFFFF0000;
    cmpb |= (dty / cdiv);
    addr.write(PWM_CMPB, cmpb);

    return 0;
}



void PWM::setPolarityA(uint dir)
{
    polA = dir?1:0;

    // Mask 0xFFFF0000 + clear left
    uint aqctlA = addr.read(PWM_AQCTLA) & 0x0000FFFF;

    if (polA)
    {
        // set CAU = 2, PRD = 1, ZRO = 1
        aqctlA |= ((2<<4) | (1<<2) | 1) << 16;
    }
    else
    {
        // set CAU = 1, PRD = 2, ZRO = 2
        aqctlA |= ((1<<4) | (2<<2) | 2) << 16;
    }

    addr.write(PWM_AQCTLA, aqctlA);
}




void PWM::setPolarityB(uint dir)
{
    polB = dir ? 1 : 0;

    // Mask: 0x0000FFFF + clear right
    uint aqctlB = addr.read(PWM_AQCTLB) & 0xFFFF0000;

    if (polB)
    {
        // set CAU = 2, PRD = 1, ZRO = 1
        aqctlB |= ((2<<4) | (1<<2) | 1);
    }
    else
    {
        // set CAU = 1, PRD = 2, ZRO = 2
        aqctlB |= ((1<<4) | (2<<2) | 2);
    }

    addr.write(PWM_AQCTLB, aqctlB);
}



uint PWM::getPeriod()
{
    return period;
}



uint PWM::getDutyA()
{
    return dutyA;
}



uint PWM::getDutyB()
{
    return dutyB;
}



uint PWM::getPolarityA()
{
    return polA;
}



uint PWM::getPolarityB()
{
    return polB;
}
