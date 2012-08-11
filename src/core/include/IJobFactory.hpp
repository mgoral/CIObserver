#ifndef IJOBFACTORY_HPP
#define IJOBFACTORY_HPP

#include "IJob.hpp"

namespace ci {

namespace core {

class IJobFactory {
public:
    virtual ~IJobFactory() {}
    virtual IJob* createJob(Url url) = 0;
    virtual IJob* createJob(Url url, Name name) = 0;
    virtual IJob* createJob(Url url, Name name, JobStatus status) = 0;
    virtual IJob* createJob(Url url, Name name, JobStatus status, JobTime time) = 0;
};

} // namespace core

} // namespace ci

#endif
