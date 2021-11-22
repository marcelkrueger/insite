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
}


void
insite::StimulationBackendInsite::initialize()
{
}

void
insite::StimulationBackendInsite::finalize()
{
}

void
insite::StimulationBackendInsite::enroll( nest::StimulationDevice& device, const nest::DictionaryDatum& )
{
    std::cout << "Stim Backend Enroll" << std::endl;
}


void
insite::StimulationBackendInsite::disenroll( nest::StimulationDevice& device )
{
}

void
insite::StimulationBackendInsite::prepare()
{
}

void
insite::StimulationBackendInsite::pre_run_hook()
{
}

void
insite::StimulationBackendInsite::post_run_hook()
{
}

void
insite::StimulationBackendInsite::cleanup()
{
}

