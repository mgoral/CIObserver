#include "IJobFactory.hpp"

namespace ci {
namespace core {

class IJobFactoryMock : public IJobFactory {
public:
    MOCK_METHOD1(createJob,
        IJob*(const Url& url));
    MOCK_METHOD2(createJob,
        IJob*(const Url& url, const Name& name));
    MOCK_METHOD3(createJob,
        IJob*(const Url& url, const Name& name, JobStatus status));
    MOCK_METHOD4(createJob,
        IJob*(const Url& url, const Name& name, JobStatus status, const JobTime& time));

};

}  // namespace core
}  // namespace ci

