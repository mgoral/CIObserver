#include "IJobFactory.hpp"

namespace ci {
namespace core {

class MockIJobFactory : public IJobFactory {
public:
    MOCK_METHOD1(createJob,
        IJob*(Url url));
    MOCK_METHOD2(createJob,
        IJob*(Url url, Name name));
    MOCK_METHOD3(createJob,
        IJob*(Url url, Name name, JobStatus status));
    MOCK_METHOD4(createJob,
        IJob*(Url url, Name name, JobStatus status, JobTime time));
};

}  // namespace core
}  // namespace ci

