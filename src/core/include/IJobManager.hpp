#ifndef IJOBMANAGER_HPP
#define IJOBMANAGER_HPP

#include <memory>
#include "IJob.hpp"

namespace ci {

namespace core {

typedef std::shared_ptr<IJob> IJobPtr;

/*
 * @brief Class which groups getched jobs per given Jenkins/Hudson address
 */
class IJobManager {
public:
    virtual ~IJobManager() {}

    /*
     * @brief: Add a new job with a given name, url and status.
     *         Job uniqueness is determined by their urls.
     */
    virtual void addJob(Name name, Url url, JobStatus status) = 0;

    /*
     * @brief Returns stored job based on a given Url.
     *        If no job is found, empty IJobPtr will be returned.
     */
    virtual IJobPtr getJob(Url url) const = 0;

    /*
     * @brief Returns CI instance description (usually provided by a user but
     *        also may be fetched from XML API)
     */
    virtual Description getDescription() const = 0;

    /*
     * @brief Returns CI instance name
     */
    virtual Name getName() const = 0;

    /*
     * @brief Returns CI instance URL address.
     */
    virtual Url getUrl() const = 0;

    /*
     * @brief: Remove a job with a given url from job collection.
     */
    virtual void removeJob(Url url) = 0;

    /*
     * @brief Sets CI instance description.
     */
    virtual void setDescription(Description description) = 0;

    /*
     * @brief Sets CI instance name
     */
    virtual void setName(Name name) = 0;

    /*
     * @brief Sets CI instance URL address. This function provides basic url check.
     * @return true, if url was set succesfully; false otherwise
     */
    virtual bool setUrl(Url url) = 0;
};

} // namespace core

} // namespace ci

#endif


