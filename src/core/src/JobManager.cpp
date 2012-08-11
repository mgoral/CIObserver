#include "JobManager.hpp"
#include "Job.hpp"

namespace ci {

namespace core {

JobManager::JobManager(std::shared_ptr<IJobFactory> jobFactory, const Url& url, const Name& setName)
: jobFactory(jobFactory) {
    if(setName.IsSameAs(wxT(""))) {
        name = url;
    }
    else {
        name = setName;
    }
}

//JobManager::JobManager(const JobManager& copy) { } // TODO: implement if default copy ctor is not sufficient

JobManager::~JobManager() {}

void JobManager::addJob(const Url& url, const Name& name, JobStatus status) {
    IJobPtr newJob(jobFactory->createJob(url, name, status));
    jobs.insert(newJob);
}

IJobPtr JobManager::getJob(const Url& url) const {
    IJobPtr tempJob(jobFactory->createJob(url));
    JobCollection::const_iterator it = jobs.find(tempJob);

    if(it != jobs.end()) {
        return *it;
    }
    return IJobPtr();
}

const Description& JobManager::getDescription() const {
    return description;
}

const Name& JobManager::getName() const {
    return name;
}

const Url& JobManager::getUrl() const {
    return url;
}

void JobManager::removeJob(const Url& url) {
    IJobPtr tempJob(jobFactory->createJob(url));
    jobs.erase(tempJob);
}

void JobManager::setDescription(const Description& newDescription) {
    description = newDescription;
}

void JobManager::setName(const Name& newName) {
    name = newName;
}

bool JobManager::setUrl(const Url& newUrl) {
    if(newUrl.StartsWith(wxT("http://"))) {
        url = newUrl;
        return true;
    }
    return false;
}

void JobManager::operator ()() {}

} // namespace core

} // namespace ci
