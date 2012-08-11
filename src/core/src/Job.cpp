#include <iostream>
#include <algorithm>

#include "Job.hpp"

namespace ci {

namespace core {

Job::Job(
    const Url& url, const Name& newName, JobStatus status, const JobTime& datetime
) : url(url), status(datetime, status), maxHistorySize(defaultHistorySize) {
    if(newName == wxT("")) {
        name = url;
    }
    else {
        name = newName;
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

const HistoryElement& Job::getHistoryElement(u32 pos) const {
    return history.at(pos);
}

const Name& Job::getName() const {
    return name;
}

JobStatus Job::getStatus() const {
    return status.second;
}

const JobTime& Job::getTime() const {
    return status.first;
}

size_t Job::getHistorySize() const {
    return history.size();
}

size_t Job::getMaxHistorySize() const {
    return maxHistorySize;
}

const Url& Job::getUrl() const {
    return url;
}

void Job::setStatus(JobStatus newStatus, const JobTime& statusOccurTime) {
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

