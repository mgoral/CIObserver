#include "JobManager.hpp"
#include "Job.hpp"

namespace ci {

namespace core {

JobManager::JobManager(std::shared_ptr<IJobFactory> jobFactory, Url url, Name setName)
: jobFactory(jobFactory), url(url) {
    if(setName.IsSameAs(wxT(""))) {
        name = url;
    }
    else {
        name = setName;
    }
}

//JobManager::JobManager(const JobManager& copy) { } // TODO: implement if default copy ctor is not sufficient

JobManager::~JobManager() {}

void JobManager::addJob(Url url, Name name,JobStatus status) {
    IJobPtr newJob(jobFactory->createJob(url, name, status));
    jobs.insert(newJob);
}

IJobPtr JobManager::getJob(Url url) const {
    IJobPtr tempJob(jobFactory->createJob(url));
    JobCollection::const_iterator it = jobs.find(tempJob);

    if(it != jobs.end()) {
        return *it;
    }
    return IJobPtr();
}

Description JobManager::getDescription() const {
    return description;
}

Name JobManager::getName() const {
    return name;
}

Url JobManager::getUrl() const {
    return url;
}

void JobManager::removeJob(Url url) {
    IJobPtr tempJob(jobFactory->createJob(url));
    jobs.erase(tempJob);
}

void JobManager::setDescription(wxString newDescription) {
    description = newDescription;
}

void JobManager::setName(Name newName) {
    name = newName;
}

bool JobManager::setUrl(Url newUrl) {
    if(newUrl.StartsWith(wxT("http://"))) {
        url = newUrl;
        return true;
    }
    return false;
}

void JobManager::operator ()() {}

} // namespace core

} // namespace ci
