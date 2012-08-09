#ifndef JOBMANAGER_HPP
#define JOBMANAGER_HPP

#include <vector>

#include "IJob.hpp"
#include "IJobManager.hpp"

namespace ci {

namespace core {

class JobManager : public IJobManager {
private:
    typedef std::vector<IJob> JobVector;

    CIName name;
    wxString description;
    Url url;
    JobVector jobs;

protected:
    /*
     * @brief Finds if there is added a job with a given URL in JobVector.
     */
    JobVector::iterator findJob(Url url);

    /*
     * @brief Finds if there is added a job with a given URL in JobVector.
     *        Const version.
     */
    JobVector::const_iterator findJob(Url url) const;

public:
    JobManager(Url url, CIName setName = wxT(""));
    JobManager(const JobManager& copy);
    ~JobManager();

    void addJob(JobName name, Url url, JobStatus status);
    IJob& getJob(Url url) const;
    wxString getDescription() const;
    CIName getName() const;
    Url getUrl() const;
    void removeJob(Url url);
    void setDescription(wxString description);
    void setName(CIName name);
    void setUrl(Url url);

    void operator ()();
};

} // namespace core

} // namespace ci


#endif

