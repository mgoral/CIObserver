#ifndef JOBSTATUS_HPP
#define JOBSTATUS_HPP

namespace ci {

namespace core {

enum JobStatus {
    JOB_UNKNOWN = 0,
    JOB_OK,
    JOB_FAILED,
    JOB_ERROR
};

} // namespace core

} // namespace ci

#endif

