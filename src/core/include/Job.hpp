#ifndef JOB_HPP
#define JOB_HPP

#include "IJob.hpp"

namespace ci {

namespace core {

const size_t defaultHistorySize = 5;

class Job : public IJob {
private:
    size_t maxHistorySize; /// Maximum history size. If equals 0, then history size is unlimited
    JobHistory history;
    JobName name;
    std::pair<wxDateTime, JobStatus> status;
    JobUrl url;

protected:
    virtual void updateHistory();

public:
    Job(JobName name, JobStatus status = JOB_UNKNOWN, JobTime datetime = JobTime::Now());
    virtual ~Job();

    HistoryElement getHistoryElement(u32 pos) const;
    JobName getName() const;
    JobStatus getStatus() const;
    virtual size_t getHistorySize() const;
    virtual size_t getMaxHistorySize() const;
    JobUrl getUrl() const;
    void setStatus(JobStatus newStatus, JobTime statusOccurTime = JobTime::Now());
    virtual void setHistorySize(u32 size);
};

} // namespace core

} // namespace ci

#endif

