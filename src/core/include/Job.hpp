#ifndef JOB_HPP
#define JOB_HPP

#include "IJob.hpp"

namespace ci {

namespace core {

const size_t defaultHistorySize = 5;

class Job : public IJob {
private:
    JobHistory history;
    Name name;
    Url url;
    std::pair<JobTime, JobStatus> status;
    size_t maxHistorySize; /// Maximum history size. If equals 0, then history size is unlimited

protected:
    virtual void updateHistory();

public:
    Job(const Url& url, const Name& newName = "", JobStatus status = JOB_UNKNOWN, const JobTime& datetime = JobTime());
    virtual ~Job();

    const HistoryElement& getHistoryElement(u32 pos) const;
    const Name& getName() const;
    JobStatus getStatus() const;
    const JobTime& getTime() const;
    virtual size_t getHistorySize() const;
    virtual size_t getMaxHistorySize() const;
    const Url& getUrl() const;
    void setStatus(JobStatus newStatus, const JobTime& statusOccurTime = JobTime());
    virtual void setMaxHistorySize(u32 size);
};

} // namespace core

} // namespace ci

#endif

