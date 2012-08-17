#include <Poco/Format.h>

#include "Exceptions.hpp"
#include "JobManager.hpp"
#include "Job.hpp"

namespace ci {

namespace core {

JobManager::JobManager(std::shared_ptr<IJobFactory> jobFactory, const Name& newName)
: jobFactory(jobFactory), logger(Poco::Logger::get("CI.Core.JobManager")) {
    if("" == newName) {
        poco_error(logger, _("Tried to create JobManager with an empty name!"));
        throw bad_parameter(_("JobManager empty name"));
    }
    else {
        name = newName;
    }
}

//JobManager::JobManager(const JobManager& copy) { } // TODO: implement if default copy ctor is not sufficient

JobManager::~JobManager() {}

void JobManager::addJob(const Url& url, const Name& name, JobStatus status) {
    IJobPtr newJob(jobFactory->createJob(url, name, status));

    std::pair<JobCollection::iterator,bool> ret;
    ret = jobs.insert(newJob);

    IJobPtr job = *(ret.first);

    if(false == ret.second) {
        poco_debug(logger, Poco::format(_("Job for URL %s is already in collection. Updating."), url.raw()));
        (*ret.first)->setStatus(status);
    }
    else {
        poco_debug(logger, Poco::format(_("Job for URL %s successfully added."), url.raw()));
    }
}

IJobPtr JobManager::getJob(const Url& url) const {
    // FIXME: this temporary object is HORRIBLE, so either find out smarter way to search through set or decide to use
    // the other container (like std::map, but then storing Url inside Job doesn't make sense anymore and we like Url
    // inside Job) --mgoral
    IJobPtr tempJob(jobFactory->createJob(url));
    JobCollection::const_iterator it = jobs.find(tempJob);

    if(it != jobs.end()) {
        return *it;
    }
    poco_warning(logger, _("No job found for URL: ") + url.raw());
    return IJobPtr();
}

const Description& JobManager::getDescription() const {
    return description;
}

const Name& JobManager::getName() const {
    return name;
}

void JobManager::notify(Poco::Timer& timer) {
    //TODO: implementation -- mgoral
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

} // namespace core

} // namespace ci
