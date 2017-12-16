#pragma once

#define OHL_WALLET_VERSION                                  uint32_t( 113 )

#define OHL_WALLET_MIN_PASSWORD_LENGTH                      8
#define OHL_WALLET_MIN_BRAINKEY_LENGTH                      32

#define OHL_WALLET_DEFAULT_UNLOCK_TIME_SEC                  ( 60 * 60 )

#define OHL_WALLET_DEFAULT_TRANSACTION_FEE                  10 // XTS

#define OHL_WALLET_DEFAULT_TRANSACTION_EXPIRATION_SEC       ( 60 * 60 )

#define WALLET_DEFAULT_MARKET_TRANSACTION_EXPIRATION_SEC    ( 60 * 10 )
