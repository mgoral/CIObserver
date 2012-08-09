#ifndef IJOBMANAGER_HPP
#define IJOBMANAGER_HPP

#include "IJob.hpp"

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
     */
    virtual void addJob(JobName name, Url url, JobStatus status) = 0;

    /*
     * @brief Returns stored job based on a given Url
     */
    virtual IJob& getJob(Url url) const = 0;

    /*
     * @brief Returns CI instance description (usually provided by a user but
     *        also may be fetched from XML API)
     */
    virtual wxString getDescription() const = 0;

    /*
     * @brief Returns CI instance URL address.
     */
    virtual Url getUrl() const = 0;

    /*
     * @brief: Remove a job with a given url from job collection.
     */
    virtual void removeJob(Url url) = 0;

    /*
     * @brief Set CI instance description.
     */
    virtual void setDescription(wxString description) = 0;

    /*
     * @brief Set CI instance URL address.
     */
    virtual void setUrl(Url url) = 0;
};

} // namespace core

} // namespace ci

#endif


