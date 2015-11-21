/**
  * \class PowerManagement
  *
  *  Created on: Jan 18, 2015
  *      Author: Jesse Victors
  *
  * \brief This is an API object designed as a way to provide a user with functions to manage and conserve power.
  *        Power Options: thruster esc's.
  */

#ifndef POWER_MANAGEMENT
#define POWER_MANAGEMENT

#include <memory>

#include "ILogger.h"
#include "IPowerModule.h"

class PowerManagement
{
    public:
    	/** \brief Initializes a new instance of a power interface.
          */
        PowerManagement(std::shared_ptr<IPowerModule> powerModule, std::shared_ptr<ILogger> logger);
        ~PowerManagement();

        /** \brief Turns on all connected thruster ESCs at once.
          *        This sends a value: 0xE7 via the burstEnableESC() function through the PowerModule.
          */
        void turnOnESCs();

        /** \brief Turns off all connected thruster ESCs at once.
          *        This sends a value: 0x00 via the burstEnableESC() function through the PowerModule.
          */
        void turnOffESCs();

    private:

        std::shared_ptr<ILogger> logger_;

        std::shared_ptr<IPowerModule> powerModule_;
};

#endif
