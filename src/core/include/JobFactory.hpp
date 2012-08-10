#ifndef JOBFACTORY_HPP
#define JOBFACTORY_HPP

#include "IJobFactory.hpp"

namespace ci {

namespace core {

class JobFactory : public IJobFactory {
public:
    ~JobFactory();
    IJob* createJob(Url url);
    IJob* createJob(Url url, JobName name);
    IJob* createJob(Url url, JobName name, JobStatus status);
    IJob* createJob(Url url, JobName name, JobStatus status, JobTime time);
};

} // namespace core

} // namespace ci

#endif
