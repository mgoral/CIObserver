#include "JobFactory.hpp"
#include "Job.hpp"

namespace ci {

namespace core {

IJob* createJob(Url url) {
    return new Job(url);
}

IJob* createJob(Url url, JobName name) {
    return new Job(url, name);
}

IJob* createJob(Url url, JobName name, JobStatus status) {
    return new Job(url, name, status);
}

IJob* createJob(Url url, JobName name, JobStatus status, JobTime time) {
    return new Job(url, name, status, time);
}

} // namespace core

} // namespace ci
