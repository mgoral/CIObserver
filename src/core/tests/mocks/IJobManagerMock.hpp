#ifndef IJOBMANAGERMOCK_HPP
#define IJOBMANAGERMOCK_HPP

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
    MOCK_CONST_METHOD0(getUrl,
        const Url&());
    MOCK_METHOD1(removeJob,
        void(const Url& url));
    MOCK_METHOD1(setDescription,
        void(const Description& description));
    MOCK_METHOD1(setName,
        void(const Name& name));
    MOCK_METHOD0(update,
        void());
};

}  // namespace core
}  // namespace ci

#endif

