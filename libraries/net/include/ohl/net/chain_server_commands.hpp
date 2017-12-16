#pragma once

/**
 * This is an internal header for ohlshares. It does not contain any classes or functions intended for clients.
 * It exists purely as an implementation detail, and may change at any time without notice.
 */

#include <fc/reflect/reflect.hpp>

const static uint32_t PROTOCOL_VERSION = 0;

namespace ohl { namespace net { namespace detail {
    enum chain_server_commands {
        finish = 0,
        get_blocks_from_number
    };
} } } //namespace ohl::net::detail

FC_REFLECT_ENUM(ohl::net::detail::chain_server_commands, (finish)(get_blocks_from_number))
FC_REFLECT_TYPENAME(ohl::net::detail::chain_server_commands)
