#include "JobFactory.hpp"
#include "Job.hpp"

namespace ci {

namespace core {

JobFactory::~JobFactory() {}

IJob* JobFactory::createJob(Url url) {
    return new Job(url);
}

IJob* JobFactory::createJob(Url url, Name name) {
    return new Job(url, name);
}

IJob* JobFactory::createJob(Url url, Name name, JobStatus status) {
    return new Job(url, name, status);
}

IJob* JobFactory::createJob(Url url, Name name, JobStatus status, JobTime time) {
    return new Job(url, name, status, time);
}

} // namespace core

} // namespace ci
