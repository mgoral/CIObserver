#ifndef IJOBFACTORY_HPP
#define IJOBFACTORY_HPP

#include "IJob.hpp"

namespace ci {

namespace core {

class IJobFactory {
public:
    virtual IJob* createJob(Url url) = 0;
    virtual IJob* createJob(Url url, JobName name) = 0;
    virtual IJob* createJob(Url url, JobName name, JobStatus status) = 0;
    virtual IJob* createJob(Url url, JobName name, JobStatus status, JobTime time) = 0;
};

} // namespace core

} // namespace ci

#endif
