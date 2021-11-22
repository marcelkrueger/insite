

#ifndef STIMULATION_BACKEND_INSITE_H
#define STIMULATION_BACKEND_INSITE_H

#include "stimulation_backend.h"
#include "nest_types.h"
#include "nest_time.h"
#include <set>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <mpi.h>


namespace insite
{

class StimulationBackendInsite : public nest::StimulationBackend
{
public:
  /**
   * InputBackend constructor
   * The actual initialization is happening in InputBackend::initialize()
   */
  StimulationBackendInsite();

  /**
   * InputBackend destructor
   * The actual finalization is happening in InputBackend::finalize()
   */
  ~StimulationBackendInsite() noexcept override;

  void initialize() override;

  void finalize() override;

  void enroll( nest::StimulationDevice& device, const DictionaryDatum& params ) override;

  void disenroll( nest::StimulationDevice& device ) override;

  void cleanup() override;

  void prepare() override;

  void pre_run_hook() override;

  void post_run_hook() override;

private:
  bool enrolled_;
  bool prepared_;
  nest::StimulationDevice* dev = nullptr;

};

} // namespace

#endif // STIMULATION_BACKEND_MPI_H
