#ifndef IJOB_HPP
#define IJOB_HPP

#include <deque>
#include <wx/datetime.h>

#include "GlobalTypes.hpp"
#include "JobStatus.hpp"

namespace ci {

namespace core {

typedef wxDateTime JobTime;
typedef std::pair<JobTime, JobStatus> HistoryElement;
typedef std::deque<HistoryElement> JobHistory;

/*
 * @brief Interface IJob stores and manages individual info about CI jobs and its history.
 *        History elements are stored in chronological order. First stored element is there
 *        earliest and the last one is the oldest (FILO - First In, Last Out).
 */
class IJob {
public:
    virtual ~IJob() {}

    /*
     * @brief Return a History Element
     * @param[in] pos Number of element to return
     * @return HistoryElement or there is no HistoryElement at given position, default HistoryElement constructed
     *         from default constructor
     */
    virtual HistoryElement getHistoryElement(u32 pos) const = 0;

    /*
     * @brief Return job name known from the parsed XML.
     */
    virtual Name getName() const = 0;

    /*
     * @brief Return latest job status.
     */
    virtual JobStatus getStatus() const = 0;

    /*
     * @brief Return time since job status is unchanged.
     */
    virtual JobTime getTime() const = 0;

    /*
     * @brief Return job URL.
     */
    virtual Url getUrl() const = 0;

    /*
     * @brief Change job status to a given one
     * @param[in] status Job status to be setStatus
     * @param[in] datetime Time when status change occurs. Defaults to the function invocation time.
     */
    virtual void setStatus(JobStatus status, JobTime datetime = JobTime::Now()) = 0;

    /*
     * @brief Overloaded operator==()
     */
    bool operator ==(const IJob& other) const {
        return other.getUrl() == getUrl();
    }

    /*
     * @brief Overloaded operator!=()
     */
    bool operator !=(const IJob& other) const {
        return !(other.getUrl() == getUrl());
    }
};

} // namespace core

} // namespace ci


#endif

