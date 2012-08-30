#include <algorithm>
#include <Poco/Format.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/SAX/InputSource.h>

#include "Exceptions.hpp"
#include "JobManager.hpp"
#include "Job.hpp"
#include "ConnectionFacade.hpp"

#include <Poco/URIStreamOpener.h>

namespace ci {

namespace core {

JobManager::JobManager(IConnectionFacadePtr connectionFacade, IJobFactoryPtr jobFactory, const Url& newUrl, const Name& newName)
: connectionFacade(connectionFacade), jobFactory(jobFactory), logger(Poco::Logger::get("CI.Core.JobManager")) {
    if(!setUrl(newUrl)) {
        poco_error(logger, Poco::format( _("JobManager got incorrect URL: %s"), url.raw()));
        throw bad_parameter(_("JobManager incorrect URL"));
    }
    if("" == newName) {
        name = newUrl;
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
        poco_trace(logger, Poco::format(_("Job for URL %s is already in collection. Updating."), url.raw()));
        (*ret.first)->setStatus(status);
    }
    else {
        poco_trace(logger, Poco::format(_("Job for URL %s successfully added."), url.raw()));
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
    poco_warning(logger, Poco::format(_("No job found for URL '%s'"), url.raw()));
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
    if(newUrl.substr(0,7) == "http://" || newUrl.substr(0, 8) == "https://") {
        url = newUrl;
        return true;
    }
    return false;
}

void JobManager::notify(Poco::Timer& timer) {
    poco_information(logger, Poco::format(_("Fetching %s"), url.raw()));

	Poco::URI uri(url);
    std::unique_ptr<std::istream> xml(connectionFacade->open(url));

    Poco::XML::InputSource xmlSrc(*xml);

    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> root = parser.parse(&xmlSrc);
    Poco::AutoPtr<Poco::XML::NodeList> xmlJobs = root->getElementsByTagName("job");

    Url xmlUrl;
    Name xmlName;
    JobStatus xmlStatus;
    JobCollection newJobs;
    u32 removalNo = jobs.size(); // prepare maximum jobs number to remove before adding new ones.

    for(u32 i = 0; i < xmlJobs->length(); ++i) {
        // Reset values for a new job.
        xmlUrl = "";
        xmlName = "";
        xmlStatus = JOB_UNKNOWN;

        Poco::XML::NodeIterator it(xmlJobs->item(i), Poco::XML::NodeFilter::SHOW_ELEMENT);
        Poco::XML::Node* currentNode = it.nextNode();

        while(currentNode) {
            if("name" == currentNode->nodeName()) {
                xmlName = currentNode->innerText();
            }
            else if("url" == currentNode->nodeName()) {
                xmlUrl = currentNode->innerText();
            }
            else if("color" == currentNode->nodeName()) {
                if(currentNode->innerText().substr(0, 4) == "blue") { // blue, blue_anime
                    xmlStatus = JOB_OK;
                }
                else if(currentNode->innerText().substr(0, 6) == "yellow") { // yellow, yellow_anime
                    xmlStatus = JOB_FAILED;
                }
                else if(currentNode->innerText().substr(0, 3) == "red") { // red, red_anime
                    xmlStatus = JOB_ERROR;
                }
                else {
                    xmlStatus = JOB_UNKNOWN;
                }
            }
            currentNode = it.nextNode();
        }

        // Add new jobs but also remember which jobs have been added.
        addJob(xmlUrl, xmlName, xmlStatus);
        newJobs.insert(IJobPtr(jobFactory->createJob(xmlUrl, xmlName, xmlStatus)));
    }

    // New jobs were added and existing jobs updated in above loop. Now it's time to remove legacy jobs.
    std::vector<IJobPtr> toRemove(removalNo); // at most all old jobs might be replaced with the new ones
    std::vector<IJobPtr>::iterator removeIt;

    removeIt = std::set_difference(jobs.begin(), jobs.end(), newJobs.begin(), newJobs.end(),
        toRemove.begin(), PointerCompare<IJobPtr>());

    for(u32 i; i < toRemove.size(); ++i)
        removeJob(toRemove[i]->getUrl());

    poco_debug(logger, Poco::format(_("Finished fetching %s"), url.raw()));
}

} // namespace core

} // namespace ci
