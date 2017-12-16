#pragma once
#include <memory>
#include <string>
#include <stdint.h>

#include <fc/time.hpp>

namespace ohl { namespace client { 
  namespace detail {
    class ohl_gntp_notifier_impl;
  }

  class ohl_gntp_notifier {
  public:
    ohl_gntp_notifier(const std::string& host_to_notify = "127.0.0.1", uint16_t port = 23053,
                      const std::string& ohl_instance_identifier = "OhlShares",
                      const fc::optional<std::string>& password = fc::optional<std::string>());
    ~ohl_gntp_notifier();

    void client_is_shutting_down();
    void notify_connection_count_changed(uint32_t new_connection_count);
    void notify_client_exiting_unexpectedly();
    void notify_head_block_too_old(const fc::time_point_sec head_block_age);
  private:
    std::unique_ptr<detail::ohl_gntp_notifier_impl> my;
  };
  typedef std::shared_ptr<ohl_gntp_notifier> ohl_gntp_notifier_ptr;

} } // end namespace ohl::client
