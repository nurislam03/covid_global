#ifndef __CRONTAB_H__
#define __CRONTAB_H__

#include <memory>
#include <croncpp.h>
#include <error/error.h>
#include <service.h>


namespace cta {

class Crontab {

    std::string cronexprstr;
    std::shared_ptr<Service> service;
    cron::cronexpr cron;

public:

    Crontab(const std::string& cronexpr, std::shared_ptr<Service> service);

    std::shared_ptr<Error> Start();

private:

    void RunNotifyJob();

};

}

#endif // __CRONTAB_H__