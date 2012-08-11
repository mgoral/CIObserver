#ifndef IJOBMOCK_HPP
#define IJOBMOCK_HPP

#include "IJob.hpp"

namespace ci {
namespace core {

class IJobMock : public IJob {
public:
    MOCK_CONST_METHOD1(getHistoryElement,
        const HistoryElement&(u32 pos));
    MOCK_CONST_METHOD0(getName,
        const Name&());
    MOCK_CONST_METHOD0(getStatus,
        JobStatus());
    MOCK_CONST_METHOD0(getTime,
        const JobTime&());
    MOCK_CONST_METHOD0(getUrl,
        const Url&());
    MOCK_METHOD2(setStatus,
        void(JobStatus status, const JobTime& datetime));
};

}  // namespace core
}  // namespace ci

#endif

