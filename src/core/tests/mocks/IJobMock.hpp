#include "IJob.hpp"

namespace ci {
namespace core {

class IJobMock : public IJob {
public:
    MOCK_CONST_METHOD1(getHistoryElement,
        HistoryElement(u32 pos));
    MOCK_CONST_METHOD0(getName,
        Name());
    MOCK_CONST_METHOD0(getStatus,
        JobStatus());
    MOCK_CONST_METHOD0(getTime,
        JobTime());
    MOCK_CONST_METHOD0(getUrl,
        Url());
    MOCK_METHOD2(setStatus,
        void(JobStatus status, JobTime datetime));
};

}  // namespace core
}  // namespace ci

