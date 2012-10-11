#ifndef IJOBMANAGER_HPP
#define IJOBMANAGER_HPP

#include "IJob.hpp"
#include "ITimerObserver.hpp"

namespace ci {

namespace core {

/*
 * @brief Class which groups getched jobs per given Jenkins/Hudson address
 */
class IJobManager {
public:
    virtual ~IJobManager() {}

    /*
     * @brief: Add a new job with a given name, url and status.
     *         Job uniqueness is determined by their urls.
     *         If a given job already exists, then it's status is updated.
     */
    virtual void addJob(const Name& name, const Url& url, JobStatus status) = 0;

    /*
     * @brief Returns stored job based on a given Url.
     *        If no job is found, empty IJobPtr will be returned.
     */
    virtual IJobPtr getJob(const Url& url) const = 0;

    /*
     * @brief Returns CI instance description (usually provided by a user but also may be fetched from XML API)
     */
    virtual const Description& getDescription() const = 0;

    /*
     * @brief Returns CI instance name
     */
    virtual const Name& getName() const = 0;

    /*
     * @brief Returns CI instance URL address.
     */
    virtual const Url& getUrl() const = 0;

    /*
     * @brief: Remove a job with a given url from job collection.
     */
    virtual void removeJob(const Url& url) = 0;

    /*
     * @brief Sets CI instance description.
     */
    virtual void setDescription(const Description& description) = 0;

    /*
     * @brief Sets CI instance name
     */
    virtual void setName(const Name& name) = 0;

    /**
     * @brief: Updates the information about jobs by parsing the web page from stored Url.
     */
    virtual void update() = 0;
};

typedef std::shared_ptr<IJobManager> IJobManagerPtr;

} // namespace core

} // namespace ci

#endif


