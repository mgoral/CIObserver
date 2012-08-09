#include <iostream>
#include <algorithm>

#include "Job.hpp"

namespace ci {

namespace core {

Job::Job(
    Url url, JobName newJobName, JobStatus status, JobTime datetime
) : url(url), status(datetime, status), maxHistorySize(defaultHistorySize) {
    if(newJobName == wxT("")) {
        name = url;
    }
    else {
        name = newJobName;
    }
}

Job::~Job()
{}

void Job::updateHistory() {
    if(maxHistorySize > 0) {
        history.push_front(status);
        if(history.size() > maxHistorySize) {
            history.pop_back();
        }
    }
}

HistoryElement Job::getHistoryElement(u32 pos) const {
    if(pos >= history.size()) {
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

Url Job::getUrl() const {
    return url;
}

void Job::setStatus(JobStatus newStatus, JobTime statusOccurTime) {
    if(status.second != newStatus && !statusOccurTime.IsEarlierThan(status.first)) {
        updateHistory();
        status.first = statusOccurTime;
        status.second = newStatus;
    }
}

void Job::setMaxHistorySize(u32 newSize) {
    maxHistorySize = newSize;
    if(history.size() > maxHistorySize) {
        JobHistory::iterator it = history.begin();
        std::advance(it, maxHistorySize);
        history.erase(it, history.end());
    }
}

} // namespace core

} // namespace ci

