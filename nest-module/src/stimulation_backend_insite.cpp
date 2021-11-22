/*
 *  stimulation_backend_mpi.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// C++ includes:
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Includes from nestkernel:
#include "stimulation_backend.h"
#include "stimulation_backend_insite.h"
#include "kernel_manager.h"
#include "stimulation_device.h"

insite::StimulationBackendInsite::StimulationBackendInsite()
  : enrolled_( false )
  , prepared_( false )
{
}

insite::StimulationBackendInsite::~StimulationBackendInsite() noexcept
{
    std::cout << "[insite] stim backend ctor" << std::endl;
}


void
insite::StimulationBackendInsite::initialize()
{
    std::cout << "[insite] stim backend init" << std::endl;
}

void
insite::StimulationBackendInsite::finalize()
{
    std::cout << "[insite] stim backend finalize" << std::endl;
}

void
insite::StimulationBackendInsite::enroll( nest::StimulationDevice& device, const DictionaryDatum& )
{
    std::cout << "[insite] stim backend enroll" << std::endl;
    dev = &device;
}


void
insite::StimulationBackendInsite::disenroll( nest::StimulationDevice& device )
{
    std::cout << "[insite] stim backend disenroll" << std::endl;
}

void
insite::StimulationBackendInsite::prepare()
{
    std::cout << "[insite] stim backend prepare" << std::endl;
}

void
insite::StimulationBackendInsite::pre_run_hook()
{
    std::cout << "[insite] stim backend pre run hook" << std::endl;
    std::vector<double> spikes;
    for (int i = 0; i < 10; i++)
    {
        double f = (double)rand() / RAND_MAX;
        spikes.push_back(f * 30);
    }
    std::cout << "generated values: " << std::endl;
    for (const auto& val : spikes)
        std::cout << val << std::endl;
    std::sort(spikes.begin(),spikes.end());
    std::cout << "generated values: " << std::endl;
    for (const auto& val : spikes)
        std::cout << val << std::endl;
    if(dev)
    {
        std::cout << "Set new stimuli" << std::endl;
        dev->set_data_from_stimulation_backend(spikes);

    }
}

void
insite::StimulationBackendInsite::post_run_hook()
{
    std::cout << "[insite] stim backend post run hook" << std::endl;
}

void
insite::StimulationBackendInsite::cleanup()
{
    std::cout << "[insite] stim backend cleanup" << std::endl;
}

