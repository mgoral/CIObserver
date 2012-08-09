#include "JobManager.hpp"

namespace ci {

namespace core {

JobManager::JobManager(Url url, CIName setName) : url(url) {
    if(setName.IsSameAs(wxT(""))) {
        name = url;
    }
    else {
        name = setName;
    }
}

JobManager::JobManager(const JobManager& copy) {

}

JobManager::~JobManager() {}

//JobVector::iterator JobManager::findJob(Url url) {}

//JobVector::iterator JobManager::findJob(Url url) const {}

void JobManager::addJob(JobName name, Url url, JobStatus status) {}

// IJob& JobManager::getJob(Url url) const {}

// wxString JobManager::getDescription() const {}

//CIName JobManager::getName() const {}

//Url JobManager::getUrl() const {}

void JobManager::removeJob(Url url) {}

void JobManager::setDescription(wxString description) {}

void JobManager::setName(CIName name) {}

void JobManager::setUrl(Url url) {}

void JobManager::operator ()() {}

} // namespace core

} // namespace ci
