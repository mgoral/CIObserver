#ifndef JOBSTATUS_HPP
#define JOBSTATUS_HPP

namespace ci {

namespace core {

enum JobStatus {
    UNKNOWN = 0,
    OK,
    FAILED,
    ERROR
};

} // namespace core

} // namespace ci

#endif

