#include <algorithm>

#include "Job.hpp"

namespace ci {

namespace core {

Job::Job(
    JobName name, wxString urlStr, JobStatus status, JobTime datetime
) : name(name), url(urlStr), status(datetime, status), maxHistorySize(defaultHistorySize)
{}

Job::~Job()
{}

void Job::updateHistory() {
    history.push_front(status);
    if(maxHistorySize != 0 && history.size() > maxHistorySize) {
        history.pop_back();
    }
}

HistoryElement Job::getHistoryElement(u32 pos) const {
    if(pos > history.size()) {
        return HistoryElement();
    }
    return history.at(pos);
}

JobName Job::getName() const {
    return name;
}

JobStatus Job::getStatus() const {
    return status.second;
}

JobTime Job::getTime() const {
    return status.first;
}

size_t Job::getHistorySize() const {
    return history.size();
}

size_t Job::getMaxHistorySize() const {
    return maxHistorySize;
}

JobUrl Job::getUrl() const {
    return url;
}

void Job::setStatus(JobStatus newStatus, JobTime statusOccurTime) {
    if(status.second != newStatus) {
        updateHistory();
        status.first = statusOccurTime;
        status.second = newStatus;
    }
}

void Job::setHistorySize(u32 newSize) {
    maxHistorySize = newSize;
    if(history.size() > maxHistorySize) {
        JobHistory::iterator it = history.begin();
        std::advance(it, maxHistorySize);
        history.erase(it, history.end());
    }
}

} // namespace core

} // namespace ci

