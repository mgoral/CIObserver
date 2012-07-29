#ifndef IJOB_HPP
#define IJOB_HPP

#include <list>
#include <wx/url.h>
#include <wx/datetime.h>

#include "GlobalTypes.hpp"
#include "JobStatus.hpp"

namespace ci {

namespace core {

typedef std::list< std::pair<wxDateTime, JobStatus> > JobHistory;
typedef wxURL JobUrl;

/*
 * @brief Interface IJob stores and manages individual info about CI jobs and its history.
 */
class IJob {
public:
    typedef wxDateTime JobTime;
    typedef std::pair<JobHistory::const_iterator, JobHistory::const_iterator> JobHistoryRange;

    virtual ~IJob() {}

    /*
     * @brief Return a pair of const_iterators to the begin and the end of JobHistory
     */
    virtual JobHistoryRange getHistory() const = 0;

    /*
     * @brief Return job name known from the parsed XML.
     */
    virtual JobName getName() const = 0;

    /*
     * @brief Return latest job status.
     */
    virtual JobStatus getStatus() const = 0;

    /*
     * @brief Return job URL.
     */
    virtual JobUrl getUrl() const = 0;

    /*
     * @brief Change job status to a given one
     * @param[in] status Job status to be setStatus
     * @param[in] datetime Time when status change occurs. Defaults to the function invocation time.
     */
    virtual void setStatus(JobStatus status, JobTime datetime = JobTime::Now()) = 0;
};

} // namespace core

} // namespace ci

bool operator ==(const ci::core::IJob& first, const ci::core::IJob& second) {
    return first.getUrl() == second.getUrl();
}

bool operator !=(const ci::core::IJob& first, const ci::core::IJob& second) {
    return !(first.getUrl() == second.getUrl());
}

#endif

