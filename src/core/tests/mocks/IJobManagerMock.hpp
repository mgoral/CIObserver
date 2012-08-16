#ifndef IJOBMANAGERMOCK_HPP
#define IJOBMANAGERMOCK_HPP

#include <Poco/Timer.h>
#include "IJobManager.hpp"

namespace ci {
namespace core {

class IJobManagerMock : public IJobManager {
public:
    MOCK_METHOD3(addJob,
        void(const Name& name, const Url& url, JobStatus status));
    MOCK_CONST_METHOD1(getJob,
        IJobPtr(const Url& url));
    MOCK_CONST_METHOD0(getDescription,
        const Description&());
    MOCK_CONST_METHOD0(getName,
        const Name&());
    MOCK_METHOD1(removeJob,
        void(const Url& url));
    MOCK_METHOD1(setDescription,
        void(const Description& description));
    MOCK_METHOD1(setName,
        void(const Name& name));
    MOCK_METHOD1(notify,
        void(Poco::Timer& timer));
};

}  // namespace core
}  // namespace ci

#endif

