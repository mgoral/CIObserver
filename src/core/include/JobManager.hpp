#ifndef JOBMANAGER_HPP
#define JOBMANAGER_HPP

#include <memory>
#include <set>

#include "IJob.hpp"
#include "IJobManager.hpp"
#include "IJobFactory.hpp"

namespace ci {

namespace core {

class JobManager : public IJobManager {
private:
    typedef std::set<IJobPtr> JobCollection;
    typedef std::shared_ptr<IJobFactory> IJobFactoryPtr;

    IJobFactoryPtr jobFactory;
    Name name;
    Description description;
    Url url;
    JobCollection jobs;

public:
    JobManager(IJobFactoryPtr jobFactory, Url url, Name setName = wxT(""));
    //JobManager(const JobManager& copy); // TODO: implement if default copy ctor is not sufficient
    ~JobManager();

    void addJob(Url url, Name name, JobStatus status);
    IJobPtr getJob(Url url) const;
    Description getDescription() const;
    Name getName() const;
    Url getUrl() const;
    void removeJob(Url url);
    void setDescription(Description newDescription);
    void setName(Name newName);
    bool setUrl(Url newUrl);

    void operator ()();
};

} // namespace core

} // namespace ci


#endif

