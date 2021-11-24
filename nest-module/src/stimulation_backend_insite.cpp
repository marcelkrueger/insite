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
#include "rapidjson/document.h"

// Includes from nestkernel:
#include "stimulation_backend.h"
#include "stimulation_backend_insite.h"
#include "kernel_manager.h"
#include "stimulation_device.h"

using namespace rapidjson;
using namespace std;



insite::StimulationBackendInsite::StimulationBackendInsite()
  : enrolled_( false )
  , prepared_( false )
  , http_listener_{"http://0.0.0.0:9100"}
{
    http_listener_.support([this](web::http::http_request request){
        if (request.method() == "POST" && request.relative_uri().path() == "/stim")
        {
            auto req = request.extract_string().get();
            Document document;
            document.Parse(req.c_str());
            
            if (not (document.HasMember("nodeIds") && document.HasMember("spikeTimes")))
            {
                std::cout << "[insite] Either nodeIds or spikeTimes is missing" << std::endl;

                web::http::http_response response(web::http::status_codes::BadRequest);
                request.reply(response);
                return;
            }
            else if(not (document["nodeIds"].IsArray() && document["spikeTimes"].IsArray()))
            {
                std::cout << "[insite] Either nodeIds or spikeTimes not an array" << std::endl;
                web::http::http_response response(web::http::status_codes::BadRequest);
                request.reply(response);
                return;
            }
            else if (not (document["nodeIds"].Size() == document["spikeTimes"].Size()))
            {
                std::cout << "[insite] NodeIds and spikeTimes did not have the same length!" << std::endl;
                web::http::http_response response(web::http::status_codes::BadRequest);
                request.reply(response);
                return;
            }

            for (int i = 0; i < document["nodeIds"].Size(); ++i)
            {
                std::uint64_t  nodeId = document["nodeIds"][i].GetInt();
                double time = document["spikeTimes"][i].GetDouble();
                std::cout << "[insite] " << nodeId << " - " << time << std::endl;
                
                const auto stimulation_device_spikes = stimulation_spikes.find(nodeId);
                if(stimulation_device_spikes != stimulation_spikes.end())
                {
                    stimulation_device_spikes->second.push_back(time);
                }
            }

            std::cout << "[insite] Spikes stored in stimulation vector: " << std::endl;
            for (const auto& m : stimulation_spikes)
            {
                for (const auto& v : m.second)
                {
                    std::cout << "[insite] " << m.first << " - " << v << std::endl;
                }
            }

            web::http::http_response response(web::http::status_codes::OK);
            request.reply(response);
        }


    });

    http_listener_.open().wait();
    std::cout << "[insite] Started stimulation HTTP server" << std::endl;
}

insite::StimulationBackendInsite::~StimulationBackendInsite() noexcept
{
    std::cout << "[insite] Stimulation backend ctor" << std::endl;
}


void
insite::StimulationBackendInsite::initialize()
{
    std::cout << "[insite] Stimulation backend init" << std::endl;
}

void
insite::StimulationBackendInsite::finalize()
{
    std::cout << "[insite] Stimulation backend finalize" << std::endl;
}

void
insite::StimulationBackendInsite::enroll( nest::StimulationDevice& device, const DictionaryDatum& )
{
    const std::uint64_t node_id = device.get_node_id();
    if (stimulation_devices_.find(node_id) == stimulation_devices_.end())
    {
        std::cout << "[insite] Enrolled Stimulation device with id: " << node_id << std::endl;
        stimulation_devices_.insert(std::make_pair(node_id,&device));
        stimulation_spikes.insert(std::make_pair(node_id,std::vector<double>()));
    }
}


void
insite::StimulationBackendInsite::disenroll( nest::StimulationDevice& device )
{
    std::cout << "[insite] Stimulation backend disenroll" << std::endl;
}

void
insite::StimulationBackendInsite::prepare()
{
    std::cout << "[insite] Stimulation backend prepare" << std::endl;
}

void
insite::StimulationBackendInsite::pre_run_hook()
{
    std::cout << "[insite] Stimulation backend pre run hook" << std::endl;

    for (const auto& stimulation_device : stimulation_devices_)
    {
        auto device_id = stimulation_device.first;
        std::cout << "[insite] Set stimuli for device: " << device_id << std::endl;
        auto& spikes = stimulation_spikes[device_id];
        std::sort(spikes.begin(),spikes.end());
        for (const auto& spike : spikes)
            std::cout << device_id << " - " << spike << std::endl;
        stimulation_device.second->set_data_from_stimulation_backend(spikes);
    }
}

void
insite::StimulationBackendInsite::post_run_hook()
{
    std::cout << "[insite] Stimulation backend post run hook" << std::endl;
}

void
insite::StimulationBackendInsite::cleanup()
{
    std::cout << "[insite] Stimulation backend cleanup" << std::endl;
}

