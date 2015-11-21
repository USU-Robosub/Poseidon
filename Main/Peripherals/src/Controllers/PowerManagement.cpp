#include "PowerManagement.h"

PowerManagement::PowerManagement(std::shared_ptr<IPowerModule> powerModule, std::shared_ptr<ILogger> logger) :
        powerModule_(powerModule),
        logger_(logger)
{

    logger_->info("Initializing PowerManagement...");
}


PowerManagement::~PowerManagement()
{}



void PowerManagement::turnOnESCs()
{
    powerModule_->burstToggleESC(0xE7);
}



void PowerManagement::turnOffESCs()
{
    powerModule_->burstToggleESC(0x00);
}

