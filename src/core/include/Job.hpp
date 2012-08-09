#ifndef JOB_HPP
#define JOB_HPP

#include "IJob.hpp"

namespace ci {

namespace core {

const size_t defaultHistorySize = 5;

class Job : public IJob {
private:
    JobHistory history;
    JobName name;
    Url url;
    std::pair<JobTime, JobStatus> status;
    size_t maxHistorySize; /// Maximum history size. If equals 0, then history size is unlimited

protected:
    virtual void updateHistory();

public:
    Job(Url url, JobName newJobName = wxT(""), JobStatus status = JOB_UNKNOWN, JobTime datetime = JobTime::Now());
    virtual ~Job();

    HistoryElement getHistoryElement(u32 pos) const;
    JobName getName() const;
    JobStatus getStatus() const;
    JobTime getTime() const;
    virtual size_t getHistorySize() const;
    virtual size_t getMaxHistorySize() const;
    Url getUrl() const;
    void setStatus(JobStatus newStatus, JobTime statusOccurTime = JobTime::Now());
    virtual void setMaxHistorySize(u32 size);
};

} // namespace core

} // namespace ci

#endif

