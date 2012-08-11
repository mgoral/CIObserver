#include "JobFactory.hpp"
#include "Job.hpp"

namespace ci {

namespace core {

JobFactory::~JobFactory() {}

IJob* JobFactory::createJob(const Url& url) {
    return new Job(url);
}

IJob* JobFactory::createJob(const Url& url, const Name& name) {
    return new Job(url, name);
}

IJob* JobFactory::createJob(const Url& url, const Name& name, JobStatus status) {
    return new Job(url, name, status);
}

IJob* JobFactory::createJob(const Url& url, const Name& name, JobStatus status, const JobTime& time) {
    return new Job(url, name, status, time);
}

} // namespace core

} // namespace ci
