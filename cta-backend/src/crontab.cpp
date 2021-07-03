#include <thread>
#include <iostream>
#include <chrono>
#include <request/notify_request.h>
#include <crontab.h>

namespace cta {



Crontab::Crontab(const std::string& cronexprstr, std::shared_ptr<Service> service)
    : cronexprstr{cronexprstr}, service{service} {}

std::shared_ptr<Error> Crontab::Start() {

    try
    {
        cron = cron::make_cron(cronexprstr);

        std::thread([this]() {
            while(true) {

                try{
                    std::time_t now = std::time(0);
                    std::time_t next = cron::cron_next(cron, now);
                    std::this_thread::sleep_until(std::chrono::system_clock::from_time_t(next));
                } catch (const std::exception& e) {
                    std::cout << "thead exception: " << e.what() << std::endl;
                }

                RunNotifyJob();
            }
        }).detach();
    }
    catch (cron::bad_cronexpr const & e)
    {
        return std::make_shared<Error>(
            Error::CODE::ERR_NOTIFY, std::string("Error starting notifier job: ") + e.what()
        );
    }

    return nullptr;
}

void Crontab::RunNotifyJob() {
    std::cout << "Running Notify Job\n";

    auto [ _, err] = service->Serve(NotifyRequest{});
    if(err) {
        std::cout << "Error RunNotifyJob: " << err->getMessage() << std::endl;
    }
}

}