// Copyright(c) 2016 Alexander Dalshov.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#if defined(_WIN32)

#include <spdlog/details/null_mutex.h>
#include <spdlog/sinks/base_sink.h>

#ifndef NOMINMAX
#define NOMINMAX // prevent windows redefining min/max
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winbase.h>

#include <mutex>
#include <string>

namespace spdlog {
namespace sinks {
/*
 * MSVC sink (logging using OutputDebugStringA)
 */
template<typename Mutex>
class msvc_sink : public base_sink<Mutex>
{
public:
    explicit msvc_sink() {}

protected:
    void sink_it_(const details::log_msg &msg) override
    {

        memory_buf_t formatted;
        base_sink<Mutex>::formatter_->format(msg, formatted);
        OutputDebugStringA(fmt::to_string(formatted).c_str());
    }

    void flush_() override {}
};

using msvc_sink_mt = msvc_sink<std::mutex>;
using msvc_sink_st = msvc_sink<details::null_mutex>;

using windebug_sink_mt = msvc_sink_mt;
using windebug_sink_st = msvc_sink_st;

} // namespace sinks
} // namespace spdlog

#endif
