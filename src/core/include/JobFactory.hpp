#ifndef JOBFACTORY_HPP
#define JOBFACTORY_HPP

#include "IJobFactory.hpp"

namespace ci {

namespace core {

class JobFactory : public IJobFactory {
public:
    ~JobFactory();
    IJob* createJob(const Url& url);
    IJob* createJob(const Url& url, const Name& name);
    IJob* createJob(const Url& url, const Name& name, JobStatus status);
    IJob* createJob(const Url& url, const Name& name, JobStatus status, const JobTime& time);
};

} // namespace core

} // namespace ci

#endif
