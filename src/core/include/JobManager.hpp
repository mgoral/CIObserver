#ifndef JOBMANAGER_HPP
#define JOBMANAGER_HPP

#include <memory>
#include <set>
#include <Poco/Timer.h>
#include <Poco/Logger.h>

#include "Helpers.hpp"
#include "IJob.hpp"
#include "IJobManager.hpp"
#include "IJobFactory.hpp"
#include "IConnectionFacade.hpp"

namespace ci {

namespace core {

class JobManager : public IJobManager {
public:
    typedef std::shared_ptr<IJobFactory> IJobFactoryPtr;
    typedef std::shared_ptr<IConnectionFacade> IConnectionFacadePtr;

private:
    typedef std::set<IJobPtr, PointerCompare<IJobPtr> > JobCollection;

    IConnectionFacadePtr connectionFacade;
    IJobFactoryPtr jobFactory;
    Name name;
    Description description;
    Url url;
    JobCollection jobs;
    Poco::Logger& logger;

protected:
    bool setUrl(const Url& newUrl);

public:
    JobManager(IConnectionFacadePtr connectionFacade, IJobFactoryPtr jobFactory, const Url& url, const Name& setName = "");
    //JobManager(const JobManager& copy); // TODO: implement if default copy ctor is not sufficient
    ~JobManager();

    void addJob(const Url& url, const Name& name, JobStatus status);
    IJobPtr getJob(const Url& url) const;
    const Description& getDescription() const;
    const Name& getName() const;
    const Url& getUrl() const;
    void notify(Poco::Timer& timer);
    void removeJob(const Url& url);
    void setDescription(const Description& newDescription);
    void setName(const Name& newName);
    void update();
};

} // namespace core

} // namespace ci


#endif

