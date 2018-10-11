////
// @file Log.cc
// @brief
// 实现日志
//
// @author niexw
// @email xiaowen.nie.cn@gmail.com
//
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <ndsl/utils/Log.h>
#include <ndsl/utils/TimeStamp.h>

////
// @brief
// log接口
//
struct ILog
{
    virtual void init() = 0;
    virtual void log(const char *data, size_t size) = 0;
};

////
// @brief
// 日志sinker
//
struct LogSinker
{
    ILog *_M_sinks[2]; // log sink
    int _M_level;      // log级别

  public:
    LogSinker()
        : _M_level(LOG_DEBUG_LEVEL)
    {
        _M_sinks[0] = NULL;
        _M_sinks[1] = NULL;
    }
    // 不需要析构函数
};

////
// @brief
// 文件sinker
//
class FileLogSinker : public ILog
{
  private:
    int _M_file; // log文件描述符
    static const off_t MAX_LOG_FILE_SIZE = 1024 * 1024 * 4; // 16M

  public:
    FileLogSinker()
        : _M_file(-1)
    {}
    ~FileLogSinker()
    {
        if (_M_file != -1) ::close(_M_file);
    }

    void init()
    {
        char path[256];
        ndsl::utils::TimeStamp ts;
        ts.now();
        ts.to_string(path, 256);
        int len = ::strlen(path);
        sprintf(path + len, ".log");

        _M_file = ::open(
            path,                          // 路径
            O_WRONLY | O_APPEND | O_CREAT, // 追加数据
            0620);                         // 其它进程可读
        if (_M_file == -1)
            printf("unable to open %s, error = %d\n", path, errno);
    }
    void log(const char *data, size_t size)
    {
        ::write(_M_file, data, size);
        check_size();
    }

  private:
    void check_size()
    {
        struct stat state;
        ::fstat(_M_file, &state);
        if (state.st_size > MAX_LOG_FILE_SIZE) {
            ::close(_M_file);
            init();
        }
    }
};

////
// @brief
// syslog sinker
//
class SysLogSinker : public ILog
{
  public:
    void init() {}
    void log(const char *data, size_t size) { ::syslog(LOG_USER, "%s", data); }
};

////
// @brief
// 全局logger
//
static LogSinker _S_logger;
static FileLogSinker _S_file_sinker;
static SysLogSinker _S_syslog_sinker;

void set_ndsl_log_sinks(int sinks)
{
    if (sinks & LOG_SINK_FILE) {
        _S_logger._M_sinks[0] = &_S_file_sinker;
        _S_file_sinker.init();
    } else
        _S_logger._M_sinks[0] = NULL;

    if (sinks & LOG_SINK_SYSLOG) {
        _S_logger._M_sinks[1] = &_S_syslog_sinker;
        _S_syslog_sinker.init();
    } else
        _S_logger._M_sinks[1] = NULL;
}
void set_ndsl_log_level(int level) { _S_logger._M_level = level; }

void ndsl_log_into_sink(int level, const char *format, ...)
{
    // 检查log级别
    if (level < _S_logger._M_level) return;
    char buffer[4096];

    // file log
    if (_S_logger._M_sinks[0]) {
        ndsl::utils::TimeStamp ts;
        ts.now();
        buffer[0] = '[';
        ts.to_string(buffer + 1, 4096);
        int ret1 = ::strlen(buffer);
        buffer[ret1] = ']';

        int ret2 = sprintf(
            buffer + ret1 + 1,
            " lv=%d pid=%d tid=%lx ",
            level,
            ::getpid(),
            (long) ::pthread_self()); // 毫秒

        // 复制数据
        va_list ap;
        va_start(ap, format);
        int ret3 = vsnprintf(
            buffer + ret1 + ret2 + 1, 512 - ret1 - ret2 - 1, format, ap);
        if (ret3 >= 0)
            _S_logger._M_sinks[0]->log(buffer, ret1 + ret2 + ret3 + 1);
        va_end(ap);
    }

    // syslog
    if (_S_logger._M_sinks[1]) {
        int ret2 = sprintf(
            buffer,
            "lv=%d pid=%d tid=%lx ",
            level,
            ::getpid(),
            (long) ::pthread_self()); // 毫秒

        // 复制数据
        va_list ap;
        va_start(ap, format);
        int ret3 = vsnprintf(buffer + ret2, 512 - ret2, format, ap);
        if (ret3 >= 0) _S_logger._M_sinks[1]->log(buffer, ret2 + ret3);
        va_end(ap);
    }
}
